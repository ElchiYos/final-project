#include "Header.h"

void printUserInstructions() {
	printf("\t\t\t\t\t---------------------\n");
	printf("\t\t\t\t\t| user instructions |\n");
	printf("\t\t\t\t\t---------------------\n\n");
	printf("\tChoose one of the options\n");
	printf("\tselect:\tto search for a field from the data\n");
	printf("\t\tthere are 4 search options '=' '!=' '>' '<'\n");
	printf("\tFor example: select debt < -100\n");
	printf("\tset:\tto insert new data into the file\n");
	printf("\tFor example: set first name=Avi, second name=Sem, id=123456789, phone=0586533563, date=08/08/2022, debt=-50\n");
	printf("\tprint:\tto print the list of debtors\n");
	printf("\tprint-e:to print the list of error\n");
	printf("\tquit:\tto exit from the program\n\n");
	printf("Enter select \\ set \\ print \\ print-e \\ quit.\n");
}

void printList(struct client* head, char* nameOfList) {
	struct client* ptr = head;
	if (ptr == NULL) {
		printf("The %s is empty.\n", nameOfList);
		return;
	}
	printf("+--------------------------------------------------------------------------------------+\n");
	printf("|   first name   |    last name   |     id      |   phone    |    debt    |    date    |\n");
	while (ptr) {
		if (ptr->debt <= 0)
			printNode(ptr);
		ptr = ptr->next;
	}
	printf("+----------------+----------------+-------------+------------+------------+------------+\n");
	printf("\n");
}

void printNode(struct client* ptr) {
	printf("+----------------+----------------+-------------+------------+------------+------------+\n");
	printf("| %-14s ", ptr->firstName);
	printf("| %-14s ", ptr->lastName);
	printf("|  %09s  ", ptr->id);
	printf("| %010s ", ptr->phoneNum);
	printf("| %10.2f ", ptr->debt);
	printf("| %02d/%02d/%04d |\n", ptr->date.day, ptr->date.month, ptr->date.year);
	if (ptr->error > 0) {
		printf("+----------------+----------------+-------------+------------+------------+------------+\n");
		printError(ptr);
	}
}

void printError(struct client* ptr) {
	if (ptr->error & 1 << fieldlessErr)
		printf("| %-85s|\n", "missing data field");

	if (ptr->error & 1 << firstNameErr)
		printf("| %-85s|\n", "the first name is wrong");

	if (ptr->error & 1 << lastNameErr)
		printf("| %-85s|\n", "the last name is wrong");

	if (ptr->error & 1 << idErr)
		printf("| %-85s|\n", "the ID is wrong");

	if (ptr->error & 1 << phoneErr)
		printf("| %-85s|\n", "the phone number is wrong");

	if (ptr->error & 1 << debtErr)
		printf("| %-85s|\n", "the debt is wrong");

	if (ptr->error & 1 << dateErr)
		printf("| %-85s|\n", "the date is wrong");

	if (ptr->error & 1 << nameToIdErr)
		printf("| %-85s|\n", "the name does not match the ID");
}
