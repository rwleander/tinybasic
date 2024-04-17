//  runtime  - interpret and execute program

#ifndef __objRuntime
#define __objRuntime


#include "objStatement.h"
#include "objStatementList.h"
#include "objVariables.h"
#include "objExpression.h"
#include "constants.h"

class objRuntime {
public:
  objVariables varList;
  objExpression expr;
  char* tokens[MAX_TOKENS];
  int count = 0;

void begin();
bool let();
  bool print(char* output);

  int findTokens(char* text);

protected:
  char tokenData[MAX_STRING + MAX_TOKENS];
  
  void clearTokens();
  void copyTokens(char* text);
  void getTokenList();
};

#endif