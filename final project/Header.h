#pragma once

#ifndef _Header
#define _Header

#include "Debtors manager.h"


#include "Prints.h"
#include "Checks.h"
#include "Utilities.h"



//										****Elchanan Yosipov****

//-------------------------------------------------------------------------------------------------------

/* General:			reads from the file and creates a linked list sorted by the size of the debt and another list for errors
* Parameters:		head - head of the clients list
					headError - Head of the error list
					fp = a pointer to the file from which the data is read
* Return value:		none */
void CreateList(struct client** head, struct client** headError, FILE* fp);


//-------------------------------------------------------------------------------------------------------

/* General:			allocates memory to a new node and inserts values into it
* Parameters:		line - gets a line from the file
* Return value:		a pointer to new node */
struct client* createNode(char* line);


//-------------------------------------------------------------------------------------------------------

/* General:			added to the top of the list
* Parameters:		head - the head of the list into which the new node will be inserted
					temp - the new node to be inserted
* Return value:		none */
void addToHead(struct client** head, struct client* temp);


//-------------------------------------------------------------------------------------------------------

/* General:			adding the new node by sorting by debt size
* Parameters:		head - the head of the list into which the new node will be inserted
					temp - the new node to be inserted
* Return value:		none */
void addBySort(struct client** head, struct client* temp);


//-------------------------------------------------------------------------------------------------------

/* General:			checks if the id certificate exists, if it exists returns a pointer to this location and a pointer to prev location
* Parameters:		head - the head of the list in which the search is performed
					temp - the struct that I compare to the list
					prevPtr - a pointer to a pointer to the previous location, if exists the pointer will change
					ptr - a pointer to a pointer to the location, if exists the pointer will change
* Return value:		none */
void serchIfExist(struct client* head, struct client* temp, struct client** prevPtr, struct client** ptr);


//-------------------------------------------------------------------------------------------------------

/* General:			sorts a node in the list to a new position according to the size of the new debt
* Parameters:		head - head of the clients list
					ptr - the node that function re-sorts
* Return value:		none */
void sortPtr(struct client** head, struct client* ptr);


//-------------------------------------------------------------------------------------------------------

/* General:			compares 2 dates and puts the late date in the list and updates the phone
* Parameters:		node - a node in the list into which the later date will be inserted
					temp - The struct being compared
* Return value:		none */
void updateDateAndPhone(struct client* node, struct client* temp);


//-------------------------------------------------------------------------------------------------------

/* General:			checks the reception from the user and sends to the appropriate function
* Parameters:		head - gets the head of clients list
					headError - gets the head of error list
					queriesLine - gets the input the user entered
					nameOfFile - the name of the file for writing
* Return value:		the user's selection "select"\"set"\"print"\ "print-e"\ quit */
char* oneQuerie(struct client** head, struct client** headError, char* queriesLine, char* nameOfFile);


//-------------------------------------------------------------------------------------------------------

/* General:			when the user chooses Select
* Parameters:		head - gets the clients list
					line - gets the input the user entered
* Return value:		1 if there is an error and 0 if there is none */
int selectFiled(struct client* head, char* line);


//-------------------------------------------------------------------------------------------------------

/* General:			when the user chooses set, allocates memory to the struct and puts the values into it
* Parameters:		line - gets the input the user entered
* Return value:		a pointer to the new struct */
struct client* setNewLine(char* line);


//-------------------------------------------------------------------------------------------------------

/* General:			writes a new line into the file
* Parameters:		temp - the data to be written into the file
					nameOfFile - the name of the file to be written into
* Return value: none */
void writeToFile(struct client* temp, char* nameOfFile);


//-------------------------------------------------------------------------------------------------------

/* General:			free the data within the node and free the node
* Parameters:		temp - the node to be frees
* Return value:		none */
void freeNode(struct client* temp);


//-------------------------------------------------------------------------------------------------------

/* General:			frees the entire list by using freeNode
* Parameters:		head - the list to be frees
* Return value:		none */
void freeList(struct client** head);


//-------------------------------------------------------------------------------------------------------

/* General:			a generic function that compares the data in the list to the user's request
* Parameters:		head - the list that the function will compare
					fieldName - the name of the field to be compared
					(*compar)(void*, void*) - a pointer to a generic function that compares the first name or last name or ID ...
					comp - a generic variable that contains the thing to be compared
					op - the operator the user entered ( = / != / > / < )
* Return value:		none */
void findField(struct client* head, char* fieldName, int(*compar)(void*, void*), void* comp, char op);


//-------------------------------------------------------------------------------------------------------

/* General:			inserts a date string into a date structure
* Parameters:		str - the string with the date
					temp - the struct into which the date will be inserted
* Return value:		the number of values successfully received from the string */
int enterStrToDate(char* str, struct Date* temp);


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
