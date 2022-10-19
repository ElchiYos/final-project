#include "Header.h"

int checkIfAllFieldFull(struct client* temp) {
	if (temp->date.day == 0 || temp->date.month == 0 || temp->date.year == 0 || temp->firstName == NULL ||
		temp->lastName == NULL || temp->id == NULL || temp->phoneNum == NULL) //checking if all fields exist
		return 1;
	return 0;
}

int checkIfTheDataIsCorrect(struct client* temp) {
	int flag = 0;

	if (checkIfAllLetters(temp->firstName)) { // check first name
		temp->error = temp->error | (1 << firstNameErr);
		flag = 1;
	}
	if (checkIfAllLetters(temp->lastName)) { // check last name
		temp->error = temp->error | (1 << lastNameErr);
		flag = 1;
	}
	if ((strlen(temp->id) > 9 || strlen(temp->id) < 5 || checkIfAllNumbers(temp->id))) { // check id
		temp->error = temp->error | (1 << idErr);
		flag = 1;
	}
	if ((strlen(temp->phoneNum) > 10 || strlen(temp->phoneNum) < 9 || (strlen(temp->phoneNum) == 10 && temp->phoneNum[0] != '0') || checkIfAllNumbers(temp->phoneNum))) { // check phone number
		temp->error = temp->error | (1 << phoneErr);
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


