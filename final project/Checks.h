#pragma once
#include "Debtors manager.h"

//-------------------------------------------------------------------------------------------------------

/* General:			checks if all strings are letters
* Parameters:		str - the string being tested
* Return value:		0 if all are letters and 1 if not */
int checkIfAllLetters(char* str);


//-------------------------------------------------------------------------------------------------------

/* General:			checks if all strings are numbers '-', '.' or '/'
* Parameters:		str - the string being tested
* Return value:		0 if all are numbers and 1 if not */
int checkIfAllNumbers(char* str);


//-------------------------------------------------------------------------------------------------------

/* General:			checks if there is no field equal to NULL
* Parameters:		temp - the tested struct
* Return value:		0 if everything is full and 1 if not  */
int checkIfAllFieldFull(struct client* temp);


//-------------------------------------------------------------------------------------------------------

/* General:			check if first name, last name, id and phone number are correct
* Parameters:		temp - the tested struct
* Return value:		0 if correct and 1 if there is an error */
int checkIfTheDataIsCorrect(struct client* temp);


//-------------------------------------------------------------------------------------------------------

/* General:			check if date is correct
* Parameters:		date - the tested struct
* Return value:		0 if correct and 1 if there is an error */
int checkDate(struct Date date);


//-------------------------------------------------------------------------------------------------------

/* General:			check if ID is correct
* Parameters:		ID - the tested string
* Return value:		0 if correct and 1 if there is an error */
int checkID(char* ID);


//-------------------------------------------------------------------------------------------------------

/* General:			check if phone number is correct
* Parameters:		phone - the tested string
* Return value:		0 if correct and 1 if there is an error */
int checkPhone(char* phone);

//-------------------------------------------------------------------------------------------------------