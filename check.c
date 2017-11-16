/*Shl syntax checker*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"syntax.h"
char* arithExpValidate(char*);
FILE *fout = NULL;
int errorFlag = 0;
int checkSyntax(char *fnam)
{
	FILE * fin = NULL;
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
						errorFlag++;
					}
					line_no = temp;
					break;
				}
				case 2 ://keyword validation
				{
					if(!validKey(tok))
					{
						fprintf(fout,"Invalid keyword : %s\n",tok);
						errorFlag++;
					}
					else
					{
						k_type = validKey(tok);
						if(eoshl)
						{
							fprintf(fout,"No instruction is allowed after 'end'\n");
							++errorFlag;	
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
							errorFlag++;
						}
					}
					else if(k_type==3)//goto
					{
						if(!validNum(tok))
						{
							fprintf(fout,"Invalid argument after 'goto' : %s\n",tok);
							errorFlag++;	
						}
					}
					else if(k_type == 4 || k_type == 5)//let,if
					{
						//expression validation
						char *p = tok, exp_flag = 0;
						while(*p != '\0')
						{
							char var[100], op[100], i = 0;//max SHL op length = 2
							while( *p!='\0' && *p!='(' && *p!=')' && !isOp(*p))
							{	
								var[i++] = *p++;
							}
							var[i] = '\0';
							if(i)
							{
								if(!validVar(var))
								{
									fprintf(fout,"Invalid variable name in expression after %s : %s\n",kword,var);
									errorFlag++;
									exp_flag++;
								}
								p--;
							}
							i = 0;
							while(isOp(*p))
							{
								op[i++] = *p++;
							}
							op[i] = '\0';
							if(i)
							{
								if(!validOp(op))
								{
									fprintf(fout,"Invalid operator detected in expression after %s : %s\n",kword, op);
									errorFlag++;
									exp_flag++;
								}
								p--;
							}
							p++;
						}
						if(exp_flag)
						{
							char * err_msg = arithExpValidate(tok);
							if(err_msg)
							{
								fprintf(fout,"Expression Validator says : %s\n",err_msg);
								errorFlag++;
								free(err_msg);
							}
						}
					}
					else if(k_type == 6)//end
					{
						fprintf(fout,"Invalid argument after %s : %s\n",kword,tok);
						errorFlag++;
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
							errorFlag++;
						}
					}
					else//print,let,input,end
					{
						fprintf(fout,"Excess argument after %s : %s\n",kword,tok);
						errorFlag++;
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
							errorFlag++;	
						}
					}
					else
					{
						fprintf(fout,"Excess argument after %s : %s\n",kword,tok);
						errorFlag++;
					}
					break;
					break;
				}
				default :
					if(k_type == 1)break;
					fprintf(fout,"Excess argument after %s : %s\n",kword,tok);
					errorFlag++;
			}
			printf("%s ", tok);//x
			tok = strtok(NULL,d);
		}
		if(tok_count != 0) //x
		{
			if(errorFlag==0)printf("\t\t(~~OK~~)");//x
			puts("");//x
		}
	}
	if(eoshl == 0)
	{
		fprintf(fout,"Parsing completes without getting any 'end'\n");
		errorFlag++;
	}
	fclose(fin);
	fclose(fout);
	return errorFlag;
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
int isOp(char c)
{
	if(c == '+'|| c == '-' || c == '*' || c == '/') return 1;
	if(c == '=' || c == '<' || c == '>' || c == '!') return 1;
	return 0;
}
int validOp(char *op)
{
	if(strlen(op) == 1)
		return isOp(op[0]);
	else if(!strcmp(op,"<=") || !strcmp(op,">=") || !strcmp(op,"==") || !strcmp(op,"!="))
		return 1;
	return 0;
}
