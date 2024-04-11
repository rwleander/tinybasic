//  expression parser and calculator

#include "constants.h"

#define MAX_OPERATORS 5

class objExpression {
public:
  char* tokens[MAX_TOKENS];
  int count = 0;
  
  void clear();
    void copy(char* values[], int n1, int n2);
	bool isOperator(char* value);
	int getPrecedence(char* value);
	
	
protected:
	  char* operators[MAX_OPERATORS] = {"+", "-", "*", "/", "^"};
};
	