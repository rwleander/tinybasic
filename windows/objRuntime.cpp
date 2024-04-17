//  objRuntime implementation

#include "objRuntime.h"
#include "objStatement.h"
#include "objStatementList.h"
#include "objVariables.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//  initialize 

void objRuntime::begin() {	
	varList.begin();
}

//  execute let statement

bool objRuntime::let() {
	char var;
	float value;
	
	
	//  make sure we have the correct format
	
	if (count < 4) return FALSE;
	if (strcmp(tokens[2], "=") != 0) return FALSE;
	
	//  make sure we have a valid variable
	
	var = tokens[1][0];
	if ((var < 'A') || (var > 'Z')) return FALSE;
	
	//  now evaluate the expression
	
	value = expr.evaluate(tokens, 3, count - 1, varList);
	varList.setVariable(var, value);
	
	return TRUE;
}

//  execute print statement and fill output_iterator//  note: return 0 if success, 1 if fail

bool objRuntime::print(char* output) {
    if (count < 2) {
        strcpy(output, "");
        return TRUE;
    }
    
    strcpy(output, tokens[1]);
    return TRUE;
}

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
    bool inQuotes = FALSE;
    
    char ch;
    char last = ' ';
    int tx = 0;  //  pointer to token  buffer
    
    //  loop through the text, copying tokens
    for (int i=0; i<strlen(text); i++) {
        ch = text[i];
    
switch(ch) {
    case '"':
      inQuotes = ! inQuotes;
	  break;
    
    case ' ':      	
      if (inQuotes == TRUE) {
        tokenData[tx] = ch;
        tx++;
        break;
      }
    
		if (last != ' ') {              
        tokenData[tx] = '\0';
        tx++;
    }
    last = ' ';
    break;

case ',':
case ';':
case '(':
case ')':

      if (inQuotes == TRUE) {
        tokenData[tx] = ch;
        tx++;
        break;
      }
    
if (last != ' ') {
    tokenData[tx] = '\0';
    tx++;
}   

tokenData[tx] = ch;
tokenData[tx + 1] = '\0';
tx += 2;
last = ' ';
break;

    default:
    tokenData[tx] = ch;
    tx++;   
    last = ch;
    break;
}   
    }   

if (last != ' ') {  
    tokenData[tx] = '\0';
}
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
