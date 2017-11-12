/*Shl syntax checker*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"syntax.h"
int checkSyntax(char *fnam)
{
	FILE * fin = NULL, *fout = NULL;
	int flag = 0;
	fin = fopen(fnam,"r");
	fout = fopen(error_details,"w");
	
	fprintf(fout,"** Report for '%s' **\n",fnam);
	if(fin == NULL)//validation
	{
		fprintf(fout,"Error in opening file. Check entered file name again.\n");
		fclose(fout);
		return 0;
	}
	
	//going through the file
	char line[100];
	int line_no = 0, eoshl = 0;//end of SHL
	while( fgets(line,100,fin) != NULL )
	{
		char * tok = NULL, * d = " \t\n";
		int tok_count = 0, k_type = -1;
		char temp_line[100], kword[10];//temporary

		strcpy(temp_line,line);//x
		tok = strtok(line , d);
		while(tok != NULL)
		{	
			tok_count++;
			switch(tok_count)
			{
				case 1 ://line number validation
				{
					int temp = atoi(tok);
					if(!validNum(tok) || temp - line_no != 1)
					{
						fprintf(fout,"Invalid line number : %s\n",tok);
						flag++;
					}
					line_no = temp;
					break;
				}
				case 2 ://keyword validation
				{
					if(!validKey(tok))
					{
						fprintf(fout,"Invalid keyword : %s\n",tok);
						flag++;
					}
					else
					{
						k_type = validKey(tok);
						if(eoshl)
						{
							fprintf(fout,"No instruction allowed after 'end'\n");
							++flag;	
						}						
						if(k_type == 6)
							eoshl++;
						strcpy(kword,tok);
					}
					break;
				}
				case 3 ://expected argument validation
				{
					if(k_type==1);//rem
					else if(k_type==2)//input,print
					{
						if(!validVar(tok))
						{
							fprintf(fout,"Invalid variable name after '%s': %s\n",kword,tok);
							flag++;
						}
					}
					else if(k_type==3)//goto
					{
						if(!validNum(tok))
						{
							fprintf(fout,"Invalid argument after 'goto' : %s\n",tok);
							flag++;	
						}
					}
					else if(k_type == 4 || k_type == 5)//let,if
					{
						char exp[20],*temp, *de = "<+-*/=>";
						strcpy(exp,tok);	
						temp = strtok(exp, de);
						while(temp != NULL)//checking variables inside an expression
						{
							if(!validVar(temp))
							{
								fprintf(fout,"Invalid variable name in expression after %s : %s\n",kword,temp);
								flag++;
							}
							temp = strtok(NULL, de);
						}
						tok = strtok(temp_line, d);
						int t = 1;
						while(t++ != tok_count){//resetting pointer
							tok = strtok(NULL, d);
						}
					}
					else if(k_type == 6)//end
					{
						fprintf(fout,"Invalid argument after %s : %s\n",kword,tok);
						flag++;
					}
					break;
				}
				case 4 :
				{
					if(k_type == 1);//rem
					else if(k_type == 5)//if
					{
						if(strcmp(tok, "goto"))
						{
							fprintf(fout,"Expected goto after 'if' : %s\n",tok);
							flag++;
						}
					}
					else//print,let,input,end
					{
						fprintf(fout,"Excess argument after %s : %s\n",kword,tok);
						flag++;
					}
					break;
				}
				case 5 :
				{
					if(k_type == 1);//rem
					else if(k_type == 5)//if....goto
					{
						if(!validNum(tok))
						{
							fprintf(fout,"Invalid argument after 'goto' : %s\n",tok);
							flag++;	
						}
					}
					else
					{
						fprintf(fout,"Excess argument after %s : %s\n",kword,tok);
						flag++;
					}
					break;
					break;
				}
				default :
					if(k_type == 1)break;
					fprintf(fout,"Excess argument after %s : %s\n",kword,tok);
					flag++;
			}
			printf("%s ", tok);//x
			tok = strtok(NULL,d);
		}
		if(tok_count != 0) //x
		{
			if(flag==0)printf("\t\t(~~OK~~)");//x
			puts("");//x
		}
	}
	if(eoshl == 0)
	{
		fprintf(fout,"Parsing completes without getting any 'end'\n");
		flag++;
	}
	fclose(fin);
	fclose(fout);
	return flag;
}
int validKey(char *kword)
{
	if(strcmp(kword,"rem") == 0)
		return 1;
	else if(strcmp(kword,"input") == 0 || strcmp(kword,"print") == 0)
		return 2;
	else if(strcmp(kword,"goto") == 0)
		return 3;
	else if(strcmp(kword,"let") == 0)
		return 4;
	else if(strcmp(kword,"if") == 0)
		return 5;
	else if(strcmp(kword,"end") == 0)
		return 6;
	else
		return 0;
}

int validVar(char *var)
{
	if(strlen(var) > 1) return 0;
	if(var[0] < 'a' || var[0] > 'z')return 0;
	return 1;
}
int validNum(char *n)
{
	while(*n != '\0')
	{
		if(*n < '0' || *n > '9')
			return 0;
		n++;
	}
	return 1;
}
