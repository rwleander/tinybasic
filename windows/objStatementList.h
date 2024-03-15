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
  
  //  helper methods - should be private
  
  int find(int sequence);
  void replace(objStatement* stmt, int n);
  void insert(objStatement* stmt, int n);
};