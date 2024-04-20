//  objStatementList.h - list of all program statements

#ifndef __objStatementList
#define __objStatementList

#include "objStatement.h"
#include "constants.h"

class objStatementList {
public:
  objStatement* statementList[MAX_LINES];
  int count;

  void begin();
  void clear();
  int add(objStatement* stmt);
  int getSequence(int i);
  char* getText(int i);  
  int find(int sequence);

//  helper methods - should be private
  
  void replace(objStatement* stmt, int n);
  void insert(objStatement* stmt, int n);
  void remove(int n);
};

#endif
