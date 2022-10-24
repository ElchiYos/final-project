#include "Checks.h"

#define MAX_DIGIT_ID 9
#define MIN_DIGIT_ID 5
#define MAX_DIGIT_PHONE 10
#define MIN_DIGIT_PHONE 9

#define MAX_DAY 31
#define MAX_MONTH 12
#define MAX_YEAR 2100

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
	if (checkID(temp->id)) { // check id
		temp->error = temp->error | (1 << idErr);
		flag = 1;
	}
	if (checkPhone(temp->phoneNum)) { // check phone number
		temp->error = temp->error | (1 << phoneErr);
		flag = 1;
	}

	if (flag == 1) return 1;
	return 0;
}

int checkID(char* ID) {
	if ((strlen(ID) > MAX_DIGIT_ID || strlen(ID) < MIN_DIGIT_ID || checkIfAllNumbers(ID))) {
		return 1;
	}
	return 0;
}

int checkPhone(char* phone) {
	if ((strlen(phone) > MAX_DIGIT_PHONE || strlen(phone) < MIN_DIGIT_PHONE || (strlen(phone) == MAX_DIGIT_PHONE && phone[0] != '0')
		|| checkIfAllNumbers(phone))) {
		return 1;
	}
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

int checkDate(struct Date date) {
	if (date.day > MAX_DAY || date.day <= 0) {
		return 0;
	}
	if (date.month > MAX_MONTH || date.month <= 0) {
		return 0;
	}
	if (date.year > MAX_YEAR || date.year <= 0) {
		return 0;
	}

	return 3;
}
	

