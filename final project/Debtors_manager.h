#pragma once

#ifndef _debtorsManagar
#define _debtorsManagar

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Date {
	char day;
	char month;
	short year;
};

struct client {
	unsigned char error;
	float debt;
	struct Date date;
	char* firstName;
	char* lastName;
	char* id;
	char* phoneNum;
	struct client* next;
};

typedef enum {
	fieldlessErr, firstNameErr, lastNameErr, idErr, phoneErr, debtErr, dateErr, nameToIdErr
}errorNum;


#endif