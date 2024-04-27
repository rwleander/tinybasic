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

//  compare two numbers

bool objExpression::compare(char* op, float f1, float f2) {	
	int i = 0;
	
	//  run the comparisons, if any are true, we're done
	
	while (i < strlen(op)) {
		switch(op[i]) {
			case '<':
			if (f1 < f2) return TRUE;
			break;
			
			case '=':
			if (f1 == f2) return TRUE;
			break;
			
			case '>':
			if (f1 > f2) return TRUE;
			break;
		}
		
		i++;
	};
		
	return FALSE;
}
	

//  see if expression is valid

bool objExpression::isValid(char* tokens[], int n1, int n2) {
	int thisTokenType = getTokenType(tokens[n1]);
	int lastTokenType = 0;
	int parenCount = 0;
	
	//  if only one expression, it must be a number or variables
	
	if (n1 == n2) {
	if (thisTokenType == __number) return TRUE;
	if (thisTokenType == __variable) return TRUE;
	return FALSE;
	}
	
	//  first item cannot be an operator
	
	if (thisTokenType == __operator) return FALSE;
	if (thisTokenType == __leftParen) parenCount++;
		
	//  check body of the expression
	//  compare each token with prior
	
	lastTokenType = thisTokenType;
		int i = n1 + 1;
		while (i <= n2) {
		thisTokenType = getTokenType(tokens[i]);
		if (thisTokenType == __unknown) return FALSE;
		
		switch (thisTokenType) {
			case __number:
			case __variable:
			if (lastTokenType == __number) return FALSE;
			if (lastTokenType == __variable) return FALSE;
			if (lastTokenType == __rightParen) return FALSE;
			break;
			
			case __operator:
			if (lastTokenType == __operator) return FALSE;
			if (lastTokenType == __leftParen) return FALSE;
			break;
			
			case __leftParen:
			if (lastTokenType == __number) return FALSE;
			if (lastTokenType == __variable) return FALSE;
			parenCount++;
			break;
			
			case __rightParen:
			if (lastTokenType == __operator) return FALSE;
			parenCount--;
			break;					
			}		
			
			lastTokenType = thisTokenType;
			i++;
	}
	
// 		last token cannot be an operator
		
		if (getTokenType(tokens[n2]) == __operator) return FALSE;
		
		//  make sure parens match
		
		if (parenCount != 0) return FALSE;
	
return TRUE;	
	}
	
//  determine token typedef

int objExpression::getTokenType(char* token) {
	
	//  parens
	
	if (strcmp(token, "(") == 0) return __leftParen;
	if (strcmp(token,")") == 0) return __rightParen;
	
	//  operator
	
	if (isOperator(token) == TRUE) return __operator;
	
	//  numbers
	
	if (isNumeric(token) == TRUE) return __number;
	
	//  variables - starts with letter
	
	if ((token[0] >= 'A') && (token[0] <= 'Z')) return __variable;
	
	return __unknown;
}

//-------------------
//  helper methods

//  check if token is a comparison

bool objExpression::isComparison(char* value) {
	char* ops[] = {"=", "<", "<=", "<>", ">", ">="};
	char* op;
	int count = 6; 
	int i = 0;
	
	while (i < count) {
		op = ops[i];
		if (strcmp(value, op) == 0) return TRUE;
		i++;
	}
	
	return FALSE;
}

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

//  is this string numeric

bool objExpression::isNumeric(char* token) {
char ch;
bool isNum = FALSE;
int i = 0;


	while (i < strlen(token)) {
		ch = token[i];
	isNum = FALSE;
	if ((ch >= '0') && (ch <= '9')) isNum = TRUE;
	if (ch == '.') isNum = TRUE;
	if (ch == '-') isNum = TRUE;
	if (ch == '+') isNum = TRUE;
	
	if (isNum == FALSE) return FALSE;
	
i++;	
	}
		
	return TRUE;
}


