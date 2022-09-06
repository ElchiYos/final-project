#include "Header.h"

int compareFirstName(void* var1, void* var2) {
	return strcmp(((struct client*)var1)->firstName, (char*)var2);
}

int compareLastName(void* var1, void* var2) {
	return strcmp(((struct client*)var1)->lastName, (char*)var2);
}

int compareID(void* var1, void* var2) {
	return atoi(((struct client*)var1)->id) - atoi((char*)var2);
}

int comparePhone(void* var1, void* var2) {
	return atoi(((struct client*)var1)->phoneNum) - atoi((char*)var2);
}

int compareDebt(void* var1, void* var2) {
	if (((struct client*)var1)->debt - *((float*)var2) > 0) return 1;
	if (((struct client*)var1)->debt - *((float*)var2) < 0) return -1;
	return 0;
}

int compareDates(void* var1, void* var2) {
	if (((struct client*)var1)->date.year - ((struct Date*)var2)->year)
		return ((struct client*)var1)->date.year - ((struct Date*)var2)->year;
	if (((struct client*)var1)->date.month - ((struct Date*)var2)->month)
		return ((struct client*)var1)->date.month - ((struct Date*)var2)->month;
	return ((struct client*)var1)->date.day - ((struct Date*)var2)->day;
}


int main() {
	struct manageList storeList = { 0 }, manageError = { 0 }; // Creating 2 lists for client and errors, and resetting them
	char* queriesLine; // pointer to a request to be received from the user
	char* tempChoose; // a temporary variable that will point to the user's choice (select/set/print/qwit)
	char choosing[7] = { 0 }; //  a variable that will point to the user's choice (select/set/print/qwit)
	FILE* fp = NULL;
	char* nameOfFile = (char*)malloc(sizeof(char) * 9); 
	if (nameOfFile != NULL) { // if the assignment was successful
		strcpy(nameOfFile, "list.csv");
		fp = fopen(nameOfFile, "r");
	}
	while (fp == NULL) { // if opening the file was not successful
		free(nameOfFile); //
		printf("Failed to open file\n");
		printf("Please enter a new name to file: ");
		nameOfFile = readinput(stdin); // receiving from the user a new name for the file
		if (nameOfFile == NULL) // if the allocation was unsuccessful
			continue;
		fp = fopen(nameOfFile, "r");
	}

	CreateList(&storeList, &manageError, fp); // Creating the lists of client and errors by reading from the file
	printList(&storeList, "list"); //printing the client list
	printList(&manageError, "error list"); // printing the error list
	fclose(fp);

	printUserInstructions();

	while (strcmp(choosing, "quit") != 0) { // stop condition when user enters quit
		printf("--->\n");
		queriesLine = readinput(stdin);// receiving from the user and allocating memory
		tempChoose = oneQuerie(&storeList, &manageError, queriesLine, nameOfFile); // analyzes the user request
		strcpy(choosing, tempChoose); // so that it is possible to free tempChoose
		free(tempChoose);
		free(queriesLine);
	}
	free(nameOfFile);
	freeList(&storeList);
	freeList(&manageError);
	return 0;
}