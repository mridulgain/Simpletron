//error report
#define error_details "error.det"
/*
	error reports are stored in file "error.det"
*/
int checkSyntax(char *);
/*
description for checkSyntax(): checks SHL syntax
	arguments:
		takes input a file name in string format
	returns :
		 0 ~ if file contains valid shl
		 else
		 	 ~ no errors found in the given shl
	also generates a file named "error.det" reporting detected errors.
*/
int validKey(char *);
/*
	description for validKey(): checks if the inputed token is a valid keyword or not 
	arguments :
		a string
	returns :
		0 ~ invalid keyword
		1~ rem 
		2~ input/print
		3~ goto
		4~ let
		5~ if
		6~ end
*/
int validVar(char *);
/*
	description of validVar() : verifies the SHL variable name
	rule : small caps one alphabet only
*/
int validNum(char *);
/*
	description of validNum() : verifies if inputed string contains valid integer or not
	returns 
		1 if valid integer
		0 otherwise
*/
int validOp(char *);
/*
	description of validOp() : verifies if given string is valid operatior or not
	returns
		1~ valid
		0~ invalid
	allowed operator list : "==" , ">=", "<=", "<", ">", "="  
*/
