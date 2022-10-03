#include "Header.h"

#define CHUNK_BUF 10
#define FIRST_CHUNK_BUF 200

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
char* readinput(FILE* fp) {
	char* input = NULL, * temp;
	char firstBuf[FIRST_CHUNK_BUF];
	char tempbuf[CHUNK_BUF];
	int inputlen = 0, templen = 0;

	if (fgets(firstBuf, FIRST_CHUNK_BUF, fp) == NULL) return NULL;
	inputlen = (int)strlen(firstBuf);
	input = malloc(inputlen * sizeof(char) + 1);
	if (input == NULL) {
		return input;
	}
	strcpy(input, firstBuf);
	if (inputlen == FIRST_CHUNK_BUF - 1 && firstBuf[inputlen - 2] != '\n') {
		do {
			fgets(tempbuf, CHUNK_BUF, fp); // receiving 10 characters from the user, if the end of the file is reached, NULL will be returned
			templen = (int)strlen(tempbuf);
			temp = realloc(input, inputlen + templen + 1); // allocation of space for the input according to the new size
			input = temp; // avoid warnings
			if (input == NULL) {
				return input;
			}
			strcpy(input + inputlen, tempbuf);
			inputlen += templen;
		} while (templen == CHUNK_BUF - 1 && tempbuf[CHUNK_BUF - 2] != '\n');// Stop condition if less than 10 characters are received or the last character is '\n'

	}

	input[inputlen - 1] = '\0'; // delete the '\n'
	return input;
}


void CreateList(struct manageList* list, struct manageList* listError, FILE* fp) {
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
			//freeNode(temp);
			temp->error = temp->error * 10 + 8;
			addToHead(listError, temp);
			continue;
		}
		checkIfTheDataIsCorrect(temp);
		serchIfExist(list, temp, &prevPtr, &ptr); // if exist inserts values into prevPtr and ptr
		if (ptr != NULL && (strcmp(ptr->firstName, temp->firstName) || strcmp(ptr->lastName, temp->lastName))) //if ID exist but difrent name
			temp->error = temp->error * 10 + 9;

		if (temp->error > 0) {
			addToHead(listError, temp);// insert into a listError  
			continue;
		}

		if (ptr != NULL) {//if exist
			ptr->debt += temp->debt; // The debt scheme
			updateDateAndPhone(ptr, temp); // update date

			if (list->head->next != NULL)  // if there is only one node in the list, there is no need to sort
				sortPtr(list, prevPtr); // new sort by new debt
			freeNode(temp);
			continue;
		}

		if (list->head == NULL) { // if the list empty
			addToHead(list, temp);
			continue;
		}
		addBySort(list, temp); // add node by sort
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
	if (token!=NULL && checkIfAllNumbers(token)) { // checks if input from a given file and checks the correctness of the input
		newClient->error = newClient->error * 10 + 5;
	}
	else {
	newClient->debt = (float)atof(token);
	}
	token = strtok(NULL, ",");
	if (token != NULL && (checkIfAllNumbers(token) || enterStrToDate(token, &newClient->date) != 3)) { // checks if input from a given file and checks the correctness of the input
		newClient->error = newClient->error * 10 + 6;
	}
	free(line);
	return newClient;
}


void addToHead(struct manageList* list, struct client* temp)
{
	list->size++;
	if (list->head == NULL) // if the list empty
	{
		list->tail = temp;
	}

	temp->next = list->head;
	list->head = temp;
}


void addBySort(struct manageList* list, struct client* temp)
{
	struct client* ptr = list->head;
	while (ptr->next) {
		if (ptr->next->debt < temp->debt) // find the prev of smaller value
			break;

		ptr = ptr->next;
	}

	//if (ptr == list->head) {
		if (ptr == list->head && ptr->debt < temp->debt) { //enter befor the head
			addToHead(list, temp);
		//	return;
		//}
		//else { // enter after the head
		//	temp->next = list->head->next;
		//	list->head->next = temp;
		//	if (temp->next == NULL) {
		//		list->tail = temp;
		//	}
			list->size++;
			return;
		}
	//}
	list->size++;
	temp->next = ptr->next;
	ptr->next = temp;
	if (temp->next == NULL)
		list->tail = temp;
}

void serchIfExist(struct manageList* list, struct client* temp, struct client** prevPtrSame, struct client** ptrSame) {
	struct client* ptr = list->head, * prev = list->head;
	while (ptr) {
		if (temp->id != NULL && atoi(ptr->id) == atoi(temp->id)) // check if same id
		{
			*prevPtrSame = prev;
			*ptrSame = ptr;
			return;
		}
		if (ptr != list->head) //Not promoting the prev for the first time
			prev = prev->next;
		ptr = ptr->next;
	}
}

void sortPtr(struct manageList* list, struct client* prevPtr) {
	struct client* ptr = prevPtr->next; // ptr = the node that needs to be re-sorted
	prevPtr->next = ptr->next; // Removing "ptr" from the list
	list->size--; //subtraction from the size of the list because the next function adds 1 to the list
	addBySort(list, ptr); // re-added in sorted form
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

void printList(struct manageList* list, char* nameOfList) {
	struct client* ptr = list->head;
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
	int num, digit;
	num = ptr->error;
	while (num != 0) {
		digit = num % 10;
		switch (digit)
		{
		case 8:
			printf("| %-85s|\n", "missing data field");
			break;
		case 1:
			printf("| %-85s|\n", "the first name is wrong");
			break;
		case 2:
			printf("| %-85s|\n", "the last name is wrong");
			break;
		case 3:
			printf("| %-85s|\n", "the ID is wrong");
			break;
		case 4:
			printf("| %-85s|\n", "the phone number is wrong");
			break;
		case 5:
			printf("| %-85s|\n", "the debt is wrong");
			break;
		case 6:
			printf("| %-85s|\n", "the date is wrong");
			break;
		case 9:
			printf("| %-85s|\n", "the name does not match the ID");
			break;
		}
		num /= 10;
	}
}

void fromUpperToLower(char* str) {
	char* ptrStr = str;
	while (*ptrStr != '\0') {
		if (*ptrStr >= 'A' && *ptrStr <= 'Z')
			*ptrStr += ' ';
		ptrStr++;
	}
}

int checkIfAllFieldFull(struct client* temp) {
	if (temp->date.day == 0 || temp->date.month == 0 || temp->date.year == 0 ||temp->firstName == NULL || 
		temp->lastName == NULL || temp->id == NULL || temp->phoneNum == NULL) //checking if all fields exist
		return 1; 
	return 0;
}

int checkIfTheDataIsCorrect(struct client* temp) {
	int flag = 0;
	
	if ( checkIfAllLetters(temp->firstName)) { // check first name
		temp->error = temp->error * 10 + 1;
		flag = 1;
	}
	if (checkIfAllLetters(temp->lastName)) { // check last name
		temp->error = temp->error * 10 + 2;
		flag = 1;
	}
	if ((strlen(temp->id) > 9 || strlen(temp->id) < 5 || checkIfAllNumbers(temp->id))) { // check id
		temp->error = temp->error * 10 + 3;
		flag = 1;
	}
	if ((strlen(temp->phoneNum) > 10 || strlen(temp->phoneNum) < 9 ||(strlen(temp->phoneNum) == 10 && temp->phoneNum[0] != '0') || checkIfAllNumbers(temp->phoneNum))) { // check phone number
		temp->error = temp->error * 10 + 4;
		flag = 1;
	}

	if (flag == 1) return 1;
	return 0;
}

int checkIfAllLetters(char* str) {
	char* ptrStr = str;
	while (*ptrStr != '\0') {
		if (*ptrStr >= 'a' && *ptrStr <= 'z' || *ptrStr == ' ')
			ptrStr++;
		else return 1;
	}
	return 0;
}

int checkIfAllNumbers(char* str) {
	char* ptrStr = str;
	while (*ptrStr != '\0') {
		if (*ptrStr >= '0' && *ptrStr <= '9' || *ptrStr == '-' || *ptrStr == '.' || *ptrStr == '/')
			ptrStr++;
		else return 1;
	}
	return 0;
}



char* oneQuerie(struct manageList* list, struct manageList* errorList, char* querie, char* nameOfFile) {
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
			flag = selectFiled(list, token);// returned 1 if there is error
			if (flag) {
				return choosing;
			}
		} while ((token = strtok(NULL, ",")) != NULL); //if there is more than one querie  
	}

	else if (strcmp(choosing, "set") == 0) {  // if the user selects "set"
		struct client* temp = NULL, * ptr = NULL, * prevPtr = NULL;
		temp = setNewLine(list, querie);
		if (temp == NULL) {
			return choosing;
		}
		serchIfExist(list, temp, &prevPtr, &ptr); // if exist inserts values into prevPtr and ptr
		if (ptr != NULL && (strcmp(ptr->firstName, temp->firstName) || strcmp(ptr->lastName, temp->lastName)))//if ID exist but difrent name
			temp->error = temp->error * 10 + 9;

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

			if (list->head->next != NULL)  // if not list with 1 node
				sortPtr(list, prevPtr); // new sort by new debt

			freeNode(temp);
		}
		else {
			if (list->head == NULL)
				addToHead(list, temp);
			else
				addBySort(list, temp);
		}

		return choosing;

	}

	else if (strcmp(choosing, "print") == 0) {  // if the user selects "print"
		if (!strcmp(querie, "print-e"))
			printList(errorList, "error list");
		else
			printList(list, "list");
	}
	else if (strcmp(choosing, "quit") == 0) {  // if the user selects "quit"
		printf("bye bye.");
	}

	else {
		printf("You must enter: select\\set\\print\\quit, Please try again.\n");
	}

	return choosing;
}

int selectFiled(struct manageList* list, char* line) {
	struct client* ptrList = list->head;
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
		findField(list, "first name", compareFirstName, ptr, op);
	}
	else if (!strcmp(select, "lastname")) {
		if (checkIfAllLetters(ptr)) {
			printf("The name should only be letters\n");
			free(select);
			return 1;
		}
		findField(list, "last name", compareLastName, ptr, op);
	}
	else if (!strcmp(select, "debt")) {
		if (checkIfAllNumbers(ptr)) {
			printf("The debt need to be number only\n");
			free(select);
			return 1;
		}
		float debt = (float)atof(ptr);
		findField(list, "debt", compareDebt, &debt, op);
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
		findField(list, "date", compareDates, &tempDate, op);
	}
	else if (!strcmp(select, "id")) {
		if (strlen(ptr) > 9 || strlen(ptr) < 5 || checkIfAllNumbers(ptr)) { // check id
			printf("the ID is wrong\n");
			free(select);
			return 1;
		}
		findField(list, "id", compareID, ptr, op);
	}
	else if (!strcmp(select, "phonenum")) {
		if (strlen(ptr) > 10 || strlen(ptr) < 9 || checkIfAllNumbers(ptr)) { // check phone number
			printf("the phone number is wrong\n");
			free(select);
			return 1;
		}
		findField(list, "phone num", comparePhone, ptr, op);
	}

	else {
		printf("you must select first name\\last name\\debt\\date\\id\\phone num\n");
		free(select);
		return 1; // there is error
	}
	free(select);
	return 0;
}


void findField(struct manageList* list, char* fieldName, int(*compare)(void*, void*), void* comp, char op) {
	struct client* ptrList = list->head;
	int flagFromList = 0;
	int flagFromNode;

	while (ptrList) {
		flagFromNode = 0;
			switch (op)
			{
			case '=':
				if (compare(ptrList, comp) == 0 && ptrList->debt <= 0) 
					flagFromNode = 1;
				break;
			case '!':
					if (compare(ptrList, comp) != 0 && ptrList->debt <= 0) 
						flagFromNode = 1;
				break;
			case '>':
					if (compare(ptrList, comp) > 0 && ptrList->debt <= 0) 
						flagFromNode = 1;
				break;
			case '<':
					if (compare(ptrList, comp) < 0 && ptrList->debt <= 0) 
						flagFromNode = 1;
				break;
			default: 
				break;
			}
		
		if(flagFromNode == 1) {
			printNode(ptrList);
			flagFromList = 1;
		}
		ptrList = ptrList->next;
	}
	if (flagFromList == 0) {
		printf("the %s not found.\n", fieldName);
	}
	else
		printf("+----------------+----------------+-------------+------------+------------+------------+\n");
}

struct client* setNewLine(struct manageList* list, char* line) {
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
				temp->error = temp->error * 10 + 6;
				return temp;
			}
		}

		else if (!strncmp(token, "debt=", 5)) {
			token += 5;
			if (checkIfAllNumbers(token)) {
				temp->error = temp->error * 10 + 5;
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
		if (temp->day > 31 || temp->day <= 0) {
			numScaned--;
		}
		if (temp->month > 12 || temp->month <= 0) {
			numScaned--;
		}
		if (temp->year > 2100 || temp->year <= 0) {
			numScaned--;
		}
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


char* removeAllSpaces(char* input) {
	char* out = input, *put = input;
	for (; *input != '\0'; ++input) {
		if (*input != ' ')
			*put++ = *input;
	}
	*put = '\0';

	return out;
}

void freeNode(struct client* temp) {
	free(temp->firstName);
	free(temp->lastName);
	free(temp->id);
	free(temp->phoneNum);
	free(temp);
}

void freeList(struct manageList* list) {
	struct client* temp = NULL;
	while (list->head != NULL) {
		temp = list->head;
		list->head = list->head->next;
		freeNode(temp);
	}
}