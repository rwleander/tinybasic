//  objStatementList.h - list of all program statements

#include "objStatement.h"
#define MAX_LINES 25

class objStatementList {
public:
  objStatement* statementList[MAX_LINES];
  int count;
  
  void begin();
  void clear();
  int add(objStatement* stmt);
};