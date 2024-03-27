//  objRuntime implementation

#include "objRuntime.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//  find tokens in a line of text

int objRuntime::findTokens(char* text) {
	clearTokens();
	copyTokens(text);
	getTokenList();
return count;
}


//-----------------------
//  protected methods

//  clear the token lists

void objRuntime::clearTokens() {
	int i;
	
	//  clear the text area with new lines
	
	for (int i=0; i<150; i++) {
		tokenData[i] = '\n';
	}

//  clear the token list
count = 0;	
	for (i=0; i<MAX_TOKENS; i++) {
		tokens[i] = 0;
	}
}

//  copy the text into a list of tokens separated by nulls ('\0')

void objRuntime::copyTokens(char* text) {
	char ch;
	char last = ' ';
	int tx = 0;  //  pointer to token  buffer
	
	//  loop through the text, copying tokens
	for (int i=0; i<strlen(text); i++) {
		ch = text[i];
	
switch(ch) {
	case ' ':
	if (last != ' ') {
		tokenData[tx] = '\0';
		tx++;
	}
	break;
	
	default:
	tokenData[tx] = ch;
	tx++;	
	break;
}	

last = ch;
	}	
	
	tokenData[tx] = '\0';
}

//  find the tokens in tokenData and set pointers in tokens

void objRuntime::getTokenList() {
	int i = 0;
	
	tokens[0] = tokenData;
count = 1;

while (tokenData[i] != '\n') {
	if (tokenData[i] == '\0') {
		if (tokenData[i+1] != '\n') {
tokens[count] = &tokenData[i+1];
count++;			
		}
	}
	i++;
}
}
