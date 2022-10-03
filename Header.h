#pragma once

#ifndef _Header
#define _Header

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date {
	char day;
	char month;
	short year;
};

struct client {
	int error;
	float debt;
	struct Date date;
	char* firstName;
	char* lastName;
	char* id;
	char* phoneNum;
	struct client* next;
};

struct manageList {
	struct client* head;
	struct client* tail;
	int size;
};

//										****Elchanan Yosipov****

//-------------------------------------------------------------------------------------------------------

/* General:			read from FILE* and allocates memory according to the size of the string
* Parameters:		fp - a pointer to the file from which the string will be read
* Return value:		pointer to the string after the location is allocated */
char* readinput(FILE* fp);


//-------------------------------------------------------------------------------------------------------

/* General:			reads from the file and creates a linked list sorted by the size of the debt and another list for errors
* Parameters:		list - a list of the client
					listError - a list of the error
					fp = a pointer to the file from which the data is read
* Return value:		none */
void CreateList(struct manageList* list, struct manageList* listError, FILE* fp);


//-------------------------------------------------------------------------------------------------------

/* General:			allocates memory to a new node and inserts values into it
* Parameters:		line - gets a line from the file
* Return value:		a pointer to new node */
struct client* createNode(char* line);


//-------------------------------------------------------------------------------------------------------

/* General:			added to the top of the list
* Parameters:		list - the list into which the new node will be inserted
					temp - the new node to be inserted
* Return value:		none */
void addToHead(struct manageList* list, struct client* temp);


//-------------------------------------------------------------------------------------------------------

/* General:			adding the new node by sorting by debt size
* Parameters:		list - the list into which the new node will be inserted
					temp - the new node to be inserted
* Return value:		none */
void addBySort(struct manageList* list, struct client* temp);


//-------------------------------------------------------------------------------------------------------

/* General:			checks if the id certificate exists, if it exists returns a pointer to this location and a pointer to prev location
* Parameters:		list - the list in which the search is performed
					temp - the struct that I compare to the list
					prevPtr - a pointer to a pointer to the previous location, if exists the pointer will change
					ptr - a pointer to a pointer to the location, if exists the pointer will change
* Return value:		none */
void serchIfExist(struct manageList* list, struct client* temp, struct client** prevPtr, struct client** ptr);


//-------------------------------------------------------------------------------------------------------

/* General:			sorts a node in the list to a new position according to the size of the new debt
* Parameters:		list - a list of the client
					ptr - the node that function re-sorts
* Return value:		none */
void sortPtr(struct manageList* list, struct client* ptr);


//-------------------------------------------------------------------------------------------------------

/* General:			compares 2 dates and puts the late date in the list and updates the phone
* Parameters:		node - a node in the list into which the later date will be inserted
					temp - The struct being compared
* Return value:		none */
void updateDateAndPhone(struct client* node, struct client* temp);


//-------------------------------------------------------------------------------------------------------

/* General:			prints the list by using a function printNode
* Parameters:		list - the list to be printed
					nameOfList - the name of the list
* Return value:		none */
void printList(struct manageList* list, char* nameOfList);


//-------------------------------------------------------------------------------------------------------

/* General:			prints the node and run the function printError
* Parameters:		ptr - the node to be printed
* Return value:		none */
void printNode(struct client* ptr);


//-------------------------------------------------------------------------------------------------------

/* General:			checks for errors and prints them
* Parameters:		ptr - the node where the errors are checked
* Return value:		none */
void printError(struct client* ptr);


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

/* General:			changes uppercase letters to lowercase letters
* Parameters:		str - the string in which the letters will be replaced
* Return value:		none */
void fromUpperToLower(char* str);


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

/* General:			checks the reception from the user and sends to the appropriate function
* Parameters:		list - gets the customer list
					errorList - gets the error list
					queriesLine - gets the input the user entered
					nameOfFile - the name of the file for writing
* Return value:		the user's selection "select"\"set"\"print"\ "print-e"\ quit */
char* oneQuerie(struct manageList* list, struct manageList* errorList, char* queriesLine, char* nameOfFile);


//-------------------------------------------------------------------------------------------------------

/* General:			when the user chooses Select
* Parameters:		list - gets the customer list
					line - gets the input the user entered
* Return value:		1 if there is an error and 0 if there is none */
int selectFiled(struct manageList* list, char* line);


//-------------------------------------------------------------------------------------------------------

/* General:			when the user chooses set, allocates memory to the struct and puts the values into it
* Parameters:		list - gets the customer list
					line - gets the input the user entered
* Return value:		a pointer to the new struct */
struct client* setNewLine(struct manageList* list, char* line);


//-------------------------------------------------------------------------------------------------------

/* General:			writes a new line into the file
* Parameters:		temp - the data to be written into the file
					nameOfFile - the name of the file to be written into
* Return value: none */
void writeToFile(struct client* temp, char* nameOfFile);


//-------------------------------------------------------------------------------------------------------

/* General:			deletes all spaces from the string
* Parameters:		input - the string
* Return value:		the string without spaces */
char* removeAllSpaces(char* input);


//-------------------------------------------------------------------------------------------------------

/* General:			free the data within the node and free the node
* Parameters:		temp - the node to be frees
* Return value:		none */
void freeNode(struct client* temp);


//-------------------------------------------------------------------------------------------------------

/* General:			frees the entire list by using freeNode
* Parameters:		list - the list to be frees
* Return value:		none */
void freeList(struct manageList* list);


//-------------------------------------------------------------------------------------------------------

/* General:			a generic function that compares the data in the list to the user's request
* Parameters:		list - the list that the function will compare
					fieldName - the name of the field to be compared
					(*compar)(void*, void*) - a pointer to a generic function that compares the first name or last name or ID ...
					comp - a generic variable that contains the thing to be compared
					op - the operator the user entered ( = / != / > / < )
* Return value:		none */
void findField(struct manageList* list, char* fieldName, int(*compar)(void*, void*), void* comp, char op);


//-------------------------------------------------------------------------------------------------------

/* General:			inserts a date string into a date structure
* Parameters:		str - the string with the date
					temp - the struct into which the date will be inserted
* Return value:		the number of values successfully received from the string */
int enterStrToDate(char* str, struct Date* temp);


//-------------------------------------------------------------------------------------------------------

/* General:			printing instructions for use at the beginning of the program
* Parameters:			none
* Return value:		none */
void printUserInstructions();

//-------------------------------------------------------------------------------------------------------

/* General:			specific functions for comparison
* Parameters:		var1, var2 - The fields that are intended for comparison
Return value:		0 if the variables are equal, a positive number if var1 is greater than var2 and negative number if var2 is greater than var1 */
int compareFirstName(struct client* node, void* var2);
int compareLastName(struct client* node, void* var2);
int compareID(struct client* node, void* var2);
int comparePhone(struct client* node, void* var2);
int compareDebt(struct client* node, void* var2);
int compareDates(struct client* node, void* var2);

#endif
