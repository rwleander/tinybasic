//  expression parser and calculator

#include "constants.h"

#define MAX_OPERATORS 5

class objExpression {
public:
  char* tokens[MAX_TOKENS];
  char* rpn[MAX_TOKENS];
  int count = 0;
  
  void clear();
    void copy(char* values[], int n1, int n2);
	void loadRpn();
	bool isOperator(char* value);
	int getPrecedence(char* value);
	
	
protected:
	  char* operators[MAX_OPERATORS] = {"+", "-", "*", "/", "^"};
	  char* opStack[MAX_TOKENS];
	  int opCount = 0;
	  int rpnCount = 0;

void setOperator(char* token);
	  
};
	