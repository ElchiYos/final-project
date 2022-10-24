#include "Utilities.h"

#define CHUNK_BUF 10
#define FIRST_CHUNK_BUF 200

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


void fromUpperToLower(char* str) {
	char* ptrStr = str;
	while (*ptrStr != '\0') {
		if (*ptrStr >= 'A' && *ptrStr <= 'Z')
			*ptrStr += ' ';
		ptrStr++;
	}
}

char* removeAllSpaces(char* input) {
	char* out = input, * put = input;
	for (; *input != '\0'; ++input) {
		if (*input != ' ')
			*put++ = *input;
	}
	*put = '\0';

	return out;
}