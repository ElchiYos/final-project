
#pragma once

#include <stdio.h>


/* General:			read from FILE* and allocates memory according to the size of the string
* Parameters:		fp - a pointer to the file from which the string will be read
* Return value:		pointer to the string after the location is allocated */
char* readinput(FILE* fp);


//-------------------------------------------------------------------------------------------------------

/* General:			changes uppercase letters to lowercase letters
* Parameters:		str - the string in which the letters will be replaced
* Return value:		none */
void fromUpperToLower(char* str);


//-------------------------------------------------------------------------------------------------------

/* General:			deletes all spaces from the string
* Parameters:		input - the string
* Return value:		the string without spaces */
char* removeAllSpaces(char* input);


//-------------------------------------------------------------------------------------------------------