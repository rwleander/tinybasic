//  objStatement.cpp - container for a line of basic code

#include "objStatement.h"

#include <string.h>
#include <stdio.h>

//  default constructor

objStatement::objStatement() {
	sequence = 0;
	strcpy(text, "");
}

//  constructor - split sequence and text using setLine

objStatement::objStatement(char* line) {
	setLine(line);
}

//  set line - break line into sequence and text

void objStatement::setLine(char* line) {
	char* ch = line;

	sequence = 0;
	strcpy(text, "");

	//  extract sequence

	if ((*ch >= '0') && (*ch <= '9')) {
		while ((*ch != ' ') && (*ch != '\0')) {
			sequence = 10 * sequence + (*ch - '0');
			ch++;
		}
	}

	//  skip over blanks

	if (*ch == '\0') return;
	while (*ch == ' ') ch++;

	//  copy text

	if (*ch != '\0')
		strcpy(text, ch);
}

//  reconstruct the line for list command

int objStatement::getLine(char* line) {
	int n = sprintf(line, "%d %s", sequence, text);
	return n;
}

//  make sure the text is a valid statement

bool objStatement::isValid(char* line) {
	int i = 0;

	while (i < strlen(line)) {
		if (line[i] == ' ') {
			return true;
		}

		if ((line[i] < '0') || (line[i] > '9')) {
			return false;
		}

		i++;
	}

	return true;
}
