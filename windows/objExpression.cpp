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
	
	//  calculate results
	
	float objExpression::calculate() {
		char op;
		char* lastChar[2];
		float x, y, z;
		
		
		//  if nothing in rpn list, quit
		
		if (rpnCount == 0) return 0.0;
		
		//  run the calculator
		
		calcCount = 0;		
		for (int i = 0; i < rpnCount; i++) {
			if (isOperator(rpn[i]) == TRUE) {
				if (calcCount < 2) return 0.0;
								
		op = rpn[i][0];
		x = calcStack[calcCount - 2];
		y = calcStack[calcCount - 1];
		z = 0.0;		
		//  printf("token: %s, stack count: %d, x: %f, y: %f\n", rpn[i], calcCount, x, y);
		
switch (op) {
	case '+': 
	z = x + y;
	break;
	
	case '-':
	z = x - y;
	break;
	
	case '*':
	z = x * y;
	break;
	
	case '/':
	if (y == 0.0) {
		z = 0.0;
	} 
		else {
		z = x / y;
	}
		break;
	}
	
	calcStack[calcCount - 1] = 0.0;
	calcStack[calcCount - 2] = z;
	calcCount--;	
}				
			else {				
				calcStack[calcCount] = strtof(rpn[i], lastChar);
				//  printf("Token: %s, stack count: %d, value: %f\n", rpn[i], calcCount, calcStack[calcCount]);
				calcCount++;
			}
		}			
		
		if (calcCount == 1) {
			return calcStack[0];
		}
		return 0.0;
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
	  