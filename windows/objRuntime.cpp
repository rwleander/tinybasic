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
	strcpy(msg, "");
}

//  run the program found in codeList

bool objRuntime::run(objStatementList &codeList) {	
	int i;
			
	//  setup
	
	varList.clear();	
	nextAddress = codeList.getSequence(0);
	
	//  loop through the code, executing statements
	
	while (nextAddress > 0) {
	i = codeList.findAddress(nextAddress);
	if (i < 0) {
		printf("Bad line number: %d\n", nextAddress);
		return FALSE;
	}
	
	sequence = codeList.getSequence(i);
	text  = codeList.getText(i);
	
	//  get next address}
//  if at end of code, set to -1
	
	i++;
	if (i >= codeList.count) {
		nextAddress = -1;
	}
	else {
	nextAddress = codeList.getSequence(i);
	}
	
	//  parse the statement
	
	if (findTokens(text) > 0) {
		if (runCommand() == FALSE) {
			return FALSE;
		}		
	}	
	}	

printf("Done\n");	
	return TRUE;
}

//  run a command

bool objRuntime::runCommand() {
	bool ok;
		
				//  go to 
		
		if (strcmp(tokens[0], "GOTO") == 0) {
			return runGoto();
		}
		
		// if
		
		if (strcmp(tokens[0], "IF") == 0) {
			return runIf();
		}
		
	//  let
	
	if (strcmp(tokens[0], "LET") == 0) {
		return runLet();  
	}
	
	//  print
	
		if (strcmp(tokens[0], "PRINT") == 0) {
	ok = runPrint(printerBuff);
if (ok == TRUE) {
	printf(printerBuff);
}	
return ok;
		}
		
//  input

if (strcmp(tokens[0], "INPUT") == 0) {
	return runInput();	
}

//  remark
	
	if (strcmp(tokens[0], "REM") == 0) {
		return runRem();
	}

	
	if (strcmp(tokens[0], "STOP") == 0) {
		return runStop();
	}
		//  bad statement
	
	strcpy (msg, "Unknown statement");
	return FALSE;
}

//  run the go to statement

bool objRuntime::runGoto() {
	
//  need a line number

if (count < 2) {
	strcpy(msg, "Bad statement");
	return FALSE;
}	

//  evaluate expression
if (expr.isValid(tokens, 1, count - 1) != TRUE) {
	strcpy(msg, "Bad expression");
	return FALSE;
}

nextAddress = expr.evaluate(tokens, 1, count -1, varList);
	return TRUE;
}

//  run if statement

bool objRuntime::runIf() {
	float fx1, fx2, fx3;
	int n1 = 0;
	int n2 = 0;
	int i = 1;
	bool err = FALSE;
	
	//  scan for tokens
	
	while (i < count) {
		if (expr.isComparison(tokens[i]) == TRUE) n1 = i;
		if (strcmp(tokens[i], "THEN") == 0) n2 = i;
		i++;
	}
	
	//  check for errors
	
	if (n1 * n2 == 0) {
		strcpy(msg, "Bad statement");
		return FALSE;
	}
	
//  validate  expressions

if (expr.isValid(tokens, 1, n1 - 1) != TRUE) err = TRUE; 
if (expr.isValid(tokens, n1 + 1, n2 - 1) != TRUE) err = TRUE;
if (expr.isValid(tokens, n2 + 1, count -1) != TRUE) err = TRUE;
if (err == TRUE) {
	strcpy(msg, "Bad expression");
	return FALSE;
}

//  evaluate the expressions

fx1 = expr.evaluate(tokens, 1, n1 - 1, varList);
fx2 = expr.evaluate(tokens, n1 + 1, n2 - 1, varList);
fx3 = expr.evaluate(tokens, n2 + 1, count - 1, varList);

//  do the comparison

if (expr.compare(tokens[n1], fx1, fx2) == TRUE) {
	nextAddress = fx3;
}

	return TRUE;
}

//  execute let statement

bool objRuntime::runLet() {
	char var;
	float value;
		
	//  make sure we have the correct format
	
	if (count < 4) {
		strcpy(msg, "Bad statement");
		return FALSE;
	}
	
	if (strcmp(tokens[2], "=") != 0) {
		strcpy (msg, "Bad statement");
		return FALSE;
	}
		
	//  make sure we have a valid variable
	
	var = tokens[1][0];
if ((var < 'A') || (var > 'Z')) {
strcpy(msg, "Bad statement");
		return FALSE;
		}
	
	//  now evaluate the expression
	
	if (expr.isValid(tokens, 3, count -1) != TRUE) {
		strcpy(msg, "Bad expression");
		return FALSE;
	}		
	
		value = expr.evaluate(tokens, 3, count - 1, varList);
	varList.setVariable(var, value);
	
	return TRUE;
}

//  execute print statement and fill output_iterator//  note: return 0 if success, 1 if fail

bool objRuntime::runPrint(char* output) {
	int n1 = 1;	
	int i = 1;
	bool rslt = TRUE;
		
    if (count < 2) {
        strcpy(output, "");
        return TRUE;
    }
    
	//  scan tokens to extract exressions
	//  commas generate two spaces
	
	strcpy(output, "");
while (i < count) {
		if (strcmp(tokens[i], ",") == 0) {
			if (n1 < i)  {
				if ( printExpression(output, n1, i - 1) != TRUE) return FALSE;
			}
			
			strcat(output, "  ");
			n1 = i + 1;
		}		
		
		i++;
	}
	
	if (n1 < count) {
		printExpression(output, n1, count - 1);
	}
	
	if (strcmp(tokens[count - 1], ",") != 0) {
		strcat(output, "\n");
	}
	
	return TRUE;
}
	
	//  print expressions extracted above
	
	bool objRuntime::printExpression(char* output, int n1, int n2) {
		char tempStr[20];
		float f;
		
	//  if literal, copy to output
	if (tokens[n1][0] == '"') {
		if (n1 < n2) {
			strcpy(msg, "Bad expression");
			return FALSE;
		}
		
		stripQuotes(tokens[n1]);
    strcat(output, tokens[n1]);
    return TRUE;
	}

//  evaluate expression

if (expr.isValid(tokens, n1, n2) != TRUE) {
	strcpy(msg, "Bad expression");
	return FALSE;
}	

f = expr.evaluate(tokens, n1, n2, varList);
sprintf(tempStr, "%f", f);
strcat(output, tempStr);
return TRUE;	
}


//  get a number from the keyboard

bool objRuntime::runInput() {
	char txt[20];
	char var;
	int txtLen;
	float value;
		
	//  only accept one variable
	
	if (count != 2) {
		strcpy(msg, "Bad statement");
		return FALSE;
	}
	
	var = tokens[1][0];
if ((var < 'A') || (var > 'Z')) {
strcpy(msg, "Bad statement");
		return FALSE;
		}
	
	//  get the keyboard input
	
	printf(": ");	
fgets(txt, 19, stdin);
txtLen = strlen(txt);
if (txtLen > 1) {
	txt[txtLen - 2] = '\0';
}

if (isValidNumber(txt) != TRUE) {
	strcpy(msg, "Bad input");
	return FALSE;
}

//  save the variable

value = atof(txt);
varList.setVariable(var, value);
return TRUE;	
}

//  run remark - do nothing

bool objRuntime::runRem() {
	return TRUE;
}

//  stop program

bool objRuntime::runStop() {
	nextAddress = -1;
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
	  tokenData[tx] = ch;
	  tx++;
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

//  remove quotes from string

  void objRuntime::stripQuotes(char* txt) {
  char txtWork[100];
  int l;
 
  
  //  if no text, quit
  
  if (strlen(txt) == 0) return;
  
  //  if leading quote, remove, otherwise just copy
  
  if (txt[0] == '"') {
	strcpy(txtWork, txt+1);  
  }
  else {
	  strcpy (txtWork, txt);
  }
  
  //  strip trailing quote
  
  l = strlen(txtWork) - 1;
  if (txtWork[l] == '"') {
	  txtWork[l] = '\0';
  }
  
  //  copy the results back to txt
  strcpy(txt, txtWork);  
}


//  check for valid number
bool objRuntime::isValidNumber(char* txt) {
	char ch;
	bool isValid;
	
	int txtLen = strlen(txt);
	int i = 0;
	while (i < txtLen) {
		ch = txt[i];
		isValid = FALSE;
		
		if ((ch >= '0') && (ch < '9')) isValid = TRUE;
		if (ch == '.') isValid = TRUE;
		if (ch == '-') isValid = TRUE;		
		
		if (isValid == FALSE) return FALSE;
		i++;
	}
	
	return TRUE;
}
