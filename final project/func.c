#include "Debtors manager.h"
#include "Header.h"

void CreateList(struct client** head, struct client** headError, FILE* fp) {
	struct client* temp = NULL, * prevPtr, * ptr;
	char* line;

	while ((line = readinput(fp)) != NULL) { // reads line by line from the file until EOF
		fromUpperToLower(line);
		line = removeAllSpaces(line);
		prevPtr = NULL, ptr = NULL;
		temp = createNode(line);// creat new struct
		if (temp == NULL) {
			printf("There is a problem with memory allocation\n");
			continue;
		}
		if (checkIfAllFieldFull(temp)) {
			temp->error = temp->error | (1 << fieldlessErr);
			addToHead(headError, temp);
			continue;
		}
		checkIfTheDataIsCorrect(temp);
		serchIfExist(*head, temp, &prevPtr, &ptr); // if exist inserts values into prevPtr and ptr
		if (ptr != NULL && (strcmp(ptr->firstName, temp->firstName) || strcmp(ptr->lastName, temp->lastName))) //if ID exist but difrent name
			temp->error = temp->error | (1 << nameToIdErr);

		if (temp->error > 0) {
			addToHead(headError, temp);// insert into a error list  
			continue;
		}

		if (ptr != NULL) {//if exist
			ptr->debt += temp->debt; // The debt scheme
			updateDateAndPhone(ptr, temp); // update date

			if ((*head)->next != NULL)  // if there is only one node in the list, there is no need to sort
				sortPtr(head, prevPtr); // new sort by new debt
			freeNode(temp);
			continue;
		}

		if (*head == NULL) { // if the list empty
			addToHead(head, temp);
			continue;
		}
		addBySort(head, temp); // add node by sort
	}
}

struct client* createNode(char* line) { // entering values end return struct
	struct client* newClient;
	char* token;
	newClient = (struct client*)calloc(sizeof(struct client), 1);
	if (newClient == NULL) {
		return newClient;
	}

	token = strtok(line, ",");
	newClient->firstName = _strdup(token);//In Linux, the underscore must be deleted

	token = strtok(NULL, ",");
	newClient->lastName = _strdup(token);//In Linux, the underscore must be deleted

	token = strtok(NULL, ",");
	newClient->id = _strdup(token);//In Linux, the underscore must be deleted

	token = strtok(NULL, ",");
	newClient->phoneNum = _strdup(token);//In Linux, the underscore must be deleted

	token = strtok(NULL, ",");
	if (token != NULL && checkIfAllNumbers(token)) { // checks if input from a given file and checks the correctness of the input
		newClient->error = newClient->error | (1 << debtErr);
	}
	else {
		newClient->debt = (float)atof(token);
	}
	token = strtok(NULL, ",");
	if (token != NULL && (checkIfAllNumbers(token) || enterStrToDate(token, &newClient->date) != 3)) { // checks if input from a given file and checks the correctness of the input
		newClient->error = newClient->error | (1 << dateErr);
	}
	free(line);
	return newClient;
}

void addToHead(struct client** head, struct client* temp)
{
	temp->next = *head;
	*head = temp;
}

void addBySort(struct client** head, struct client* temp)
{
	struct client* ptr = *head;
	while (ptr->next) {
		if (ptr->next->debt < temp->debt) // find the prev of smaller value
			break;

		ptr = ptr->next;
	}

	if (ptr == *head && ptr->debt < temp->debt) { //enter befor the head
		addToHead(head, temp);
		return;
	}

	temp->next = ptr->next;
	ptr->next = temp;

}

void serchIfExist(struct client* head, struct client* temp, struct client** prevPtrSame, struct client** ptrSame) {
	struct client* ptr = head, * prev = head;
	while (ptr) {
		if (temp->id != NULL && atoi(ptr->id) == atoi(temp->id)) // check if same id
		{
			*prevPtrSame = prev;
			*ptrSame = ptr;
			return;
		}
		if (ptr != head) //Not promoting the prev for the first time
			prev = prev->next;
		ptr = ptr->next;
	}
}

void sortPtr(struct client** head, struct client* prevPtr) {
	struct client* ptr = prevPtr->next; // ptr = the node that needs to be re-sorted
	prevPtr->next = ptr->next; // Removing "ptr" from the list
	addBySort(head, ptr); // re-added in sorted form
	return;
}

void updateDateAndPhone(struct client* node, struct client* temp) {
	if (compareDates(node, &temp->date) < 0) { // if the date in temp->date is later
		node->date = temp->date;
		if (strcmp(node->phoneNum, temp->phoneNum) != 0) { //if the phone is not compare
			free(node->phoneNum); // frees memory and reallocates in case the file is written without 0 in the prefix and the user entered with 0
			node->phoneNum = _strdup(temp->phoneNum);
		}
	}
}

char* oneQuerie(struct client** head, struct client** headError, char* querie, char* nameOfFile) {
	int flag = 0, tempScan; // temp to avoid a warning
	char* token;
	char* choosing = (char*)malloc(8 * (sizeof(char)));
	if (choosing == NULL || querie == NULL) return NULL; //Check that the assignment was successful
	fromUpperToLower(querie);//change to lower case
	tempScan = sscanf(querie, "%[^ -]7s", choosing); //token with the first word
	querie = removeAllSpaces(querie);

	if (strcmp(choosing, "select") == 0) // if the user selects "select"
	{
		token = strtok(querie, ",");
		do
		{
			flag = selectFiled(*head, token);// returned 1 if there is error
			if (flag) {
				return choosing;
			}
		} while ((token = strtok(NULL, ",")) != NULL); //if there is more than one querie  
	}

	else if (strcmp(choosing, "set") == 0) {  // if the user selects "set"
		struct client* temp = NULL, * ptr = NULL, * prevPtr = NULL;
		temp = setNewLine(querie);
		if (temp == NULL) {
			return choosing;
		}
		serchIfExist(*head, temp, &prevPtr, &ptr); // if exist inserts values into prevPtr and ptr
		if (ptr != NULL && (strcmp(ptr->firstName, temp->firstName) || strcmp(ptr->lastName, temp->lastName)))//if ID exist but difrent name
			temp->error = temp->error | (1 << nameToIdErr);

		if (temp->error > 0) {
			printError(temp);
			printf("You nust enter: set first name=... , second name=... ,id=... , phone=... , date=... , debt=...\n");
			freeNode(temp);
			return choosing;
		}
		writeToFile(temp, nameOfFile);

		if (ptr != NULL) { //if exist
			ptr->debt += temp->debt; // The debt scheme
			updateDateAndPhone(ptr, temp); // update date

			if ((*head)->next != NULL)  // if not list with 1 node
				sortPtr(head, prevPtr); // new sort by new debt

			freeNode(temp);
		}
		else {
			if (*head == NULL)
				addToHead(head, temp);
			else
				addBySort(head, temp);
		}
		return choosing;
	}

	else if (strcmp(choosing, "print") == 0) {  // if the user selects "print"
		if (!strcmp(querie, "print-e"))
			printList(*headError, "error list");
		else
			printList(*head, "list");
	}
	else if (strcmp(choosing, "quit") == 0) {  // if the user selects "quit"
		printf("bye bye.");
	}

	else {
		printf("You must enter: select\\set\\print\\quit, Please try again.\n");
	}
	return choosing;
}

int selectFiled(struct client* head, char* line) {
	struct client* ptrList = head;
	char* ptr = line + 6; // ptr without the first word
	char op;
	char* select = (char*)malloc((strlen(ptr) + 1) * sizeof(char));
	int temp; // to avoid a warning
	if (select == NULL) {
		printf("There is a problem with memory allocation\n");
		return 1;
	}
	temp = sscanf(ptr, "%[^=!><]s", select);
	ptr = ptr + strlen(select);
	if (*ptr == '\0') { // if the user did not enter an operator
		free(select);
		printf("The input is incorrect\n");
		return 1;
	}
	op = *ptr; // inserting the operator into the variable
	ptr++;
	if (op == '!' && *ptr != '=') { //if there is no '=' after the '!'
		free(select);
		printf("The input is incorrect\n");
		return 1;
	}
	else if (op == '!' && *ptr == '=') ptr++;

	if (!strcmp(select, "firstname")) {
		if (checkIfAllLetters(ptr)) {
			printf("The name should only be letters\n");
			free(select);
			return 1;
		}
		findField(head, "first name", compareFirstName, ptr, op);
	}
	else if (!strcmp(select, "lastname")) {
		if (checkIfAllLetters(ptr)) {
			printf("The name should only be letters\n");
			free(select);
			return 1;
		}
		findField(head, "last name", compareLastName, ptr, op);
	}
	else if (!strcmp(select, "debt")) {
		if (checkIfAllNumbers(ptr)) {
			printf("The debt need to be number only\n");
			free(select);
			return 1;
		}
		float debt = (float)atof(ptr);
		findField(head, "debt", compareDebt, &debt, op);
	}
	else if (!strcmp(select, "date")) {
		int numScaned;
		struct Date tempDate;
		numScaned = enterStrToDate(ptr, &tempDate);
		if (numScaned < 3 || checkIfAllNumbers(ptr)) {
			printf("The date is wrong\n");
			free(select);
			return 1;
		}
		findField(head, "date", compareDates, &tempDate, op);
	}
	else if (!strcmp(select, "id")) {
		if (checkID(ptr)) { // check id
			printf("the ID is wrong\n");
			free(select);
			return 1;
		}
		findField(head, "id", compareID, ptr, op);
	}
	else if (!strcmp(select, "phonenum")) {
		if (checkPhone(ptr)) { // check phone number
			printf("the phone number is wrong\n");
			free(select);
			return 1;
		}
		findField(head, "phone num", comparePhone, ptr, op);
	}

	else {
		printf("you must select first name\\last name\\debt\\date\\id\\phone num\n");
		free(select);
		return 1; // there is error
	}
	free(select);
	return 0;
}
void findField(struct client* head, char* fieldName, int(*compare)(void*, void*), void* comp, char op) {
	struct client* ptrList = head;
	int flagForList = 0;
	int flagForNode;

	while (ptrList) {
		flagForNode = 0;
		switch (op)
		{
		case '=':
			if (compare(ptrList, comp) == 0 && ptrList->debt <= 0)
				flagForNode = 1;
			break;
		case '!':
			if (compare(ptrList, comp) != 0 && ptrList->debt <= 0)
				flagForNode = 1;
			break;
		case '>':
			if (compare(ptrList, comp) > 0 && ptrList->debt <= 0)
				flagForNode = 1;
			break;
		case '<':
			if (compare(ptrList, comp) < 0 && ptrList->debt <= 0)
				flagForNode = 1;
			break;
		default:
			break;
		}

		if (flagForNode == 1) {
			printNode(ptrList);
			flagForList = 1;
		}
		ptrList = ptrList->next;
	}
	if (flagForList == 0) {
		printf("the %s not found.\n", fieldName);
	}
	else
		printf("+----------------+----------------+-------------+------------+------------+------------+\n");
}

struct client* setNewLine(char* line) {
	struct client* temp;
	char* token;
	temp = (struct client*)calloc(sizeof(struct client), 1);
	if (temp == NULL) {
		printf("There is a problem with memory allocation\n");
		return temp;
	}
	line = removeAllSpaces(line);
	fromUpperToLower(line);
	char* ptrStr = line + 3;
	token = strtok(ptrStr, ",");


	while (token != NULL)
	{
		if (!strncmp(token, "firstname=", 10)) {
			token += 10;
			temp->firstName = _strdup(token);//In Linux, the underscore must be deleted
		}

		else if (!strncmp(token, "secondname=", 11)) {
			token += 11;
			temp->lastName = _strdup(token);//In Linux, the underscore must be deleted
		}

		else if (!strncmp(token, "id=", 3)) {
			token += 3;
			temp->id = _strdup(token);//In Linux, the underscore must be deleted
		}

		else if (!strncmp(token, "phone=", 6)) {
			token += 6;
			temp->phoneNum = _strdup(token);//In Linux, the underscore must be deleted
		}

		else if (!strncmp(token, "date=", 5)) {
			token += 5;
			if (checkIfAllNumbers(token) || enterStrToDate(token, &temp->date) != 3) {
				temp->error = temp->error | (1 << dateErr);
				return temp;
			}
		}

		else if (!strncmp(token, "debt=", 5)) {
			token += 5;
			if (checkIfAllNumbers(token)) {
				temp->error = temp->error | (1 << debtErr);
				return temp;
			}
			temp->debt = (float)atof(token);
		}
		token = strtok(NULL, ",");
	}
	if (checkIfAllFieldFull(temp)) {
		freeNode(temp);
		printf("Not enough data entered\n");
		return NULL;
	}
	checkIfTheDataIsCorrect(temp);
	return temp;
}

int enterStrToDate(char* str, struct Date* temp) {
	int numScaned; // The number of data captured
	numScaned = sscanf(str, "%2hhd/%2hhd/%4hd", &temp->day, &temp->month, &temp->year);
	if (numScaned == 3) {
		numScaned = checkDate(*temp); // if the date is incorrect returned 0
	}
	return numScaned;
}

void writeToFile(struct client* temp, char* nameOfFile) {
	FILE* fp = fopen(nameOfFile, "a");
	if (fp == NULL) {
		printf("There was an error writing to the file\n");
		return;
	}
	fprintf(fp, "%s,", temp->firstName);
	fprintf(fp, "%s,", temp->lastName);
	fprintf(fp, "%09s,", temp->id);
	fprintf(fp, "%010s,", temp->phoneNum);
	fprintf(fp, "%.2f,", temp->debt);
	fprintf(fp, "%02d/%02d/%04d\n", temp->date.day, temp->date.month, temp->date.year);

	fclose(fp);
	printf("the data was saved successfully.\n");
}

void freeNode(struct client* temp) {
	free(temp->firstName);
	free(temp->lastName);
	free(temp->id);
	free(temp->phoneNum);
	free(temp);
}

void freeList(struct client** head) {
	struct client* temp = NULL;
	while (*head != NULL) {
		temp = *head;
		*head = (*head)->next;
		freeNode(temp);
	}
}