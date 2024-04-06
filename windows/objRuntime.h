//  runtime class - interpret and execute program

#include "objStatement.h"
#include "objStatementList.h"

#define MAX_TOKENS 25

class objRuntime {
	public:  
  char* tokens[MAX_TOKENS];
  int count = 0;
  
  bool print(char* output);
   
	
  int findTokens(char* text);  
  
  protected:
  char tokenData[150];
    void clearTokens();
	void copyTokens(char* text);
	void getTokenList();
	
};

