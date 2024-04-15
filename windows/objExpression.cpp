//  expression parser and calculator

#include "objExpression.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//  evaluate an expression

float objExpression::evaluate(char* values[], int n1, int n2, objVariables &vars) {
	clear();
	copy(values, n1, n2);
	loadRpn();	
	return calculate(vars);	
}
	
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
	
	
//  if left paren, add to op stack	

if (strcmp(token, "(") == 0) {
	opStack[opCount] = token;
	opCount++;
	return;
}

//  if right paren, copy any operators back from the op stack to left paren then remove paren

if (strcmp(token, ")") == 0) {
	opCount--;
	if (opCount < 0) {
		opCount = 0;
		return;
	}

	while ((strcmp(opStack[opCount], "(") != 0) && (opCount > 0)) {
		rpn[rpnCount] = opStack[opCount];
		rpnCount++;
		opCount--;		
	}
	
	return;
}

//  if last operator was open paren, add token to op stack

char* op = opStack[opCount - 1];
if (strcmp(op, "(") == 0) {
	opStack[opCount] = token;
	opCount++;
	return;
}


//  if new token has precedence over op stack, just add to stack 
 
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
	
	float objExpression::calculate(objVariables &vars) {
		char op, ch;
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
			ch = rpn[i][0];
			if ((ch >='A') && (ch <= 'Z')) {
				calcStack[calcCount] = vars.getVariable(ch);				
			}
			else {
				calcStack[calcCount] = strtof(rpn[i], lastChar);
			}
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
	  