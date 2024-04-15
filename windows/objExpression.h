//  expression parser and calculator

#include "constants.h"
#include "objVariables.h"

#define MAX_OPERATORS 7

class objExpression {
public:
  char* tokens[MAX_TOKENS];
  char* rpn[MAX_TOKENS];
  int count = 0;

float evaluate(char* values[], int n1, int n2, objVariables &vars);  
  void clear();
    void copy(char* values[], int n1, int n2);
	void loadRpn();
	float calculate(objVariables &vars);
	bool isOperator(char* value);
	int getPrecedence(char* value);
	
	
protected:
	  char* operators[MAX_OPERATORS] = {"+", "-", "*", "/", "^", "(", ")"};
	  char* opStack[MAX_TOKENS];
	  float calcStack[MAX_OPERATORS];
	  int opCount = 0;
	  int rpnCount = 0;
	  int calcCount = 0;

void setOperator(char* token);
	  
};
	