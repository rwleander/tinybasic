//  runtime class - interpret and execute program

#include "objStatement.h"
#include "objStatementList.h"
#include "constants.h"

class objRuntime {
public:
  char* tokens[MAX_TOKENS];
  int count = 0;

  bool print(char* output);

  int findTokens(char* text);

protected:
  char tokenData[MAX_STRING + MAX_TOKENS];
  
  void clearTokens();
  void copyTokens(char* text);
  void getTokenList();
};

