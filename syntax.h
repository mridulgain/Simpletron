//error report
#define error_details "error.det"

int checkSyntax(char *);
/*
description for checkSyntax(): checks SHL syntax
	arguments:
		takes input a file name in string format
	return:
		returns 1 if file contains valid shl
		returns 0 if any syntactical error is found in the given shl
	also generates a file named "error.det" with error details for given file
*/
int validKey(char *);
/*
	description for validKey(): 
	arguments :
		*/
int validVar(char *);
