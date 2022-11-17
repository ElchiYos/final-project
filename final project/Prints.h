#pragma once

#ifndef _prints
#define _prints

#include "Debtors_manager.h"


//-------------------------------------------------------------------------------------------------------

/* General:			printing instructions for use at the beginning of the program
* Parameters:			none
* Return value:		none */
void printUserInstructions();

//-------------------------------------------------------------------------------------------------------

/* General:			prints the list by using a function printNode
* Parameters:		head - the head of the list to be printed
					nameOfList - the name of the list
* Return value:		none */
void printList(struct client* head, char* nameOfList);


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


#endif


