//Arithmetic expression validation
#include<stdio.h>
//#include<conio.h>
#include<string.h>
#include<stdlib.h>

//FUNCTION PROTOTYPE
/*
Function Name: arithExpValidate
Input: Character array
Output: NULL if expression is correct
        Error message if expression is wrong
*/
char* arithExpValidate(char*);

//arithExpValidate fuction definition
char* arithExpValidate(char *exp)
{
	int i, flag = 0;
	int operandVal = 0, operatorVal = 0, equalTo = 0, bracket = 0;
	char *message = malloc(100*sizeof(char));

	int length = strlen(exp);

	//Brackets check
	for(i = 0; i < length; i++)
	{
		if(exp[i] == '(')
		{
			bracket++;
		}
		else if(exp[i] == ')')
		{
			bracket--;
			if(bracket < 0)
			{
				strcpy(message, "Brackets error detected");
				return message;
			}
		}
		else
		{
			continue;
		}
	}
	if(bracket != 0)
	{
		strcpy(message, "Brackets error detected");
		return message;
	}

	//Arithmetic expression check
	for(i = 0; i < length; i++)
	{
		//Constant as first character check
		if(i==0 && (exp[i] >= 48 && exp[i] <= 57))
		{
			strcpy(message, "Cannot store in constant");
			return message;
		}

		//Relational operator and equalTo checking
		if((exp[i] == '>' || exp[i] == '<' || exp[i] == '=' || exp[i] == '!') && exp[i+1] == '=')
		{
			equalTo++;
			i++;
			flag = 1;
		}
		else if(exp[i] == '>' || exp[i] == '<')
		{
			equalTo++;
			flag = 1;
		}
		else if(exp[i] == '=')
		{
			equalTo++;
			flag = 1;
		}
		if(flag == 1)
		{
			if((operandVal != 1 && operatorVal != 0) || equalTo > 1)
			{
				strcpy(message, "Equal to error detected.");
				return message;
			}
			operatorVal++;
			flag = 0;
			continue;
		}

		//Check operand value
		if(exp[i] >= 97 && exp[i] <= 122)
		{
			operandVal++;
			continue;
		}

		//Check operator value
		if(exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
		{
			operatorVal++;
			if((exp[i+1] >= 48 && exp[i+1] <= 57) && (exp[i-1] == '+' || exp[i-1] == '-' || exp[i-1] == '*' || exp[i-1] == '/' || exp[i-1] == '=' || exp[i-1] == '(' ))
			{
				operatorVal--;
				continue;
			}
			if(operandVal == operatorVal)
			{
				continue;
			}
			else
			{
				strcpy(message, "Extra operator/operand detected");
				return message;
			}
		}

		//Constant check
		while(exp[i] >= 48 && exp[i] <= 57)
		{
			i++;
			flag = 1;
		}
		if(flag == 1)
		{
			operandVal++;
			flag = 0;
			i--;
		}
	}//end for loop

	//Value check
	if(operandVal != operatorVal + 1)
	{
		strcpy(message, "Extra operator/operand detected");
		return message;
	}
	if(equalTo == 0)
	{
		strcpy(message, "Equal to error detected");
		return message;
	}
	strcpy(message, "NULL");
	return message;
}
