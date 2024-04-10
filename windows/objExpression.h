//  expression parser and calculator

#include "constants.h"

class objExpression {
public:
  char* tokens[MAX_TOKENS];
  int count = 0;
  
  void clear();
    void copy(char* values[], int n1, int n2);
  };
  
	  