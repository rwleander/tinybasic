//  expression parser and calculator

#include "objExpression.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



//  clear tokens

void objExpression::clear() {
	for (int i=0; i<MAX_TOKENS; i++) {
		tokens[i] = 0;
	}
	count = 0;
}

//  copy tokens 

void objExpression::copy(char* values[], int n1, int n2) {
	int i = n1;
	
	  count = 0;
	  while (i <= n2) {
			   tokens[count] = values[i];		  
		  count++;
		  i++;
	  }	  	  
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
	  