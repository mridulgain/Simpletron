/*SHL syntax checker tester*/
#include<stdio.h>
#include<string.h>
#include"syntax.h"
void main(int argc,char **argv)
{
	FILE *fp = NULL;
	int error_count;
	if( !checkSyntax("test1.shl") )
	{
		printf("OK\n");
	}
	else
	{
		printf("Messsages : \n");
		fp = fopen(error_details,"r");
		char c;
		while(!feof(fp))
		{
			c = fgetc(fp);
			putchar(c);
		}
		printf("\n");
    }
}
