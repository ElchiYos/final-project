#include "Prints.h"


void printUserInstructions() {
	puts("\t\t\t\t\t---------------------");
	puts("\t\t\t\t\t| user instructions |");
	puts("\t\t\t\t\t---------------------\n");
	puts("\tChoose one of the options");
	puts("\tselect:\tto search for a field from the data");
	puts("\t\tthere are 4 search options '=' '!=' '>' '<'");
	puts("\tFor example: select debt < -100\n");
	puts("\tset:\tto insert new data into the file");
	puts("\tFor example: set first name=Avi, second name=Sem, id=123456789, phone=0586533563, date=08/08/2022, debt=-50\n");
	puts("\tprint:\tto print the list of debtors\n");
	puts("\tprint-e:to print the list of error\n");
	puts("\tquit:\tto exit from the program\n\n");
	puts("Enter select \\ set \\ print \\ print-e \\ quit.");
}

void printList(struct client* head, char* nameOfList) {
	struct client* ptr = head;
	if (ptr == NULL) {
		printf("The %s is empty.\n", nameOfList);
		return;
	}
	puts("+--------------------------------------------------------------------------------------+");
	puts("|   first name   |    last name   |     id      |   phone    |    debt    |    date    |");
	while (ptr) {
		if (ptr->debt <= 0)
			printNode(ptr);
		ptr = ptr->next;
	}
	puts("+----------------+----------------+-------------+------------+------------+------------+");
	puts("\n");
}

void printNode(struct client* ptr) {
	puts("+----------------+----------------+-------------+------------+------------+------------+");
	printf("| %-14s ", ptr->firstName);
	printf("| %-14s ", ptr->lastName);
	printf("|  %09s  ", ptr->id);
	printf("| %010s ", ptr->phoneNum);
	printf("| %10.2f ", ptr->debt);
	printf("| %02d/%02d/%04d |\n", ptr->date.day, ptr->date.month, ptr->date.year);
	if (ptr->error > 0) {
		puts("+----------------+----------------+-------------+------------+------------+------------+");
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
