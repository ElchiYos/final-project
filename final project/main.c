#include "Header.h"
#define NAME_FILE "list.csv"
#define MAX_CHOOSE 7

int compareFirstName(struct client* node, void* var2) {
	return strcmp(node->firstName, (char*)var2);
}

int compareLastName(struct client* node, void* var2) {
	return strcmp(node->lastName, (char*)var2);
}

int compareID(struct client* node, void* var2) {
	return atoi(node->id) - atoi((char*)var2);
}

int comparePhone(struct client* node, void* var2) {
	return atoi(node->phoneNum) - atoi((char*)var2);
}

int compareDebt(struct client* node, void* var2) {
	if (node->debt - *((float*)var2) > 0) return 1;
	if (node->debt - *((float*)var2) < 0) return -1;
	return 0;
}

int compareDates(struct client* node, void* var2) {
	if (node->date.year - ((struct Date*)var2)->year)
		return node->date.year - ((struct Date*)var2)->year;
	if (node->date.month - ((struct Date*)var2)->month)
		return node->date.month - ((struct Date*)var2)->month;
	return node->date.day - ((struct Date*)var2)->day;
}


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	/*struct client* head;
	struct client* headError;*/
	struct manageList storeList = { 0 }, manageError = { 0 }; // Creating 2 lists for client and errors, and resetting them
	char* queriesLine; // pointer to a request to be received from the user
	char* tempChoose; // a temporary variable that will point to the user's choice (select/set/print/qwit)
	char choosing[MAX_CHOOSE] = { 0 }; //  a variable that will point to the user's choice (select/set/print/qwit)
	FILE* fp = NULL;
	char* nameOfFile = (char*)malloc(sizeof(char) * strlen(NAME_FILE));
	if (nameOfFile != NULL) { // if the assignment was successful
		strcpy(nameOfFile, NAME_FILE);
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
	printf("\nERROR LIST\n");
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