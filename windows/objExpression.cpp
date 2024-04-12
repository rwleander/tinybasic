//  expression parser and calculator

#include "objExpression.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



//  clear tokens

void objExpression::clear() {
	for (int i=0; i<MAX_TOKENS; i++) {
		tokens[i] = 0;
		rpn[i] = 0;
	}
	count = 0;
}

//  copy tokens 

void objExpression::copy(char* values[], int n1, int n2) {
	int i = n1;
	
	clear();
	  count = 0;
	  while (i <= n2) {
			   tokens[count] = values[i];		  
		  count++;
		  i++;
	  }	  	  
  }
  
  //  convert tokens to rpn notation
  
  void objExpression::loadRpn() {
	  char* token;
	  	  
	  //  if nothing in list, quit
	  
	  if (count == 0) return;

//  copy tokens to rpn stack

rpnCount = 0;
opCount = 0;	  
	  for (int i=0; i<count; i++) {
token =  tokens[i];

if (isOperator(token) == TRUE) {
setOperator(token);
}
else {
	rpn[rpnCount] = token;
	rpnCount++;
}	
	  }

//  copy remaining tokens
opCount--;
while (opCount >= 0) {
	rpn[rpnCount] = opStack[opCount];
	rpnCount++;
	opCount--;
}		
  }
//  place operators on rpn stack

void objExpression::setOperator(char * token) {

//  if op stack is empty, add

if (opCount == 0) {
	opStack[opCount] = token;
	opCount++;
	return;
}
	
//   if token has higher precedence than top of op stack, just address

char* op = opStack[opCount - 1];
if (getPrecedence(token) > getPrecedence(op)) {
	opStack[opCount] = token;
	opCount++;
	return;
}

//  otherwise add op to rpn list  and replace with token

rpn[rpnCount] = opStack[opCount - 1];
rpnCount++;
opStack[opCount - 1] = token;	
}
	
  
  //-------------------
  //  helper methods
  
  //  check if value is an operator
  bool objExpression::isOperator(char* value) {
	  if (getPrecedence(value) >= 0) return TRUE;
	  return FALSE;
  }
  
	  //  get operator precedence
	  
	  int objExpression::getPrecedence(char* value) {
		  int i = 0;	  
	  while (i < MAX_OPERATORS) {
		  if (strcmp(value, operators[i]) == 0) return i;
		  i++;
	  }
	  return -1;
  }
	  