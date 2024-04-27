//  expression parser and calculator

#ifndef __objExpression
#define __objExpression

#include "constants.h"
#include "objVariables.h"

#define MAX_OPERATORS 7

#define __number 1
#define __variable 2
#define __operator 3
#define __leftParen 4
#define __rightParen 5
#define __unknown 0


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
  bool compare(char* op, float f1, float f2);
  bool isValid(char* tokens[], int n1, int n2);
  bool isOperator(char* value);
  bool isComparison(char* value);
  int getPrecedence(char* value);
  int getTokenType(char* token);

protected:
  char* operators[MAX_OPERATORS] = {"+", "-", "*", "/", "^", "(", ")"};
  char* opStack[MAX_TOKENS];
  float calcStack[MAX_OPERATORS];
  int opCount = 0;
  int rpnCount = 0;
  int calcCount = 0;

  void setOperator(char* token);  
  bool isNumeric (char* token);
};

#endif