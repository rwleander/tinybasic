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
int nextAddress = 0;

void begin();
bool run(objStatementList &codeList);
bool runLet();
  bool print(char* output);

  int findTokens(char* text);

protected:
  char tokenData[MAX_STRING + MAX_TOKENS];
int sequence;
char* text;
  
  bool runCommand();
  void clearTokens();
  void copyTokens(char* text);
  void getTokenList();
};

#endif