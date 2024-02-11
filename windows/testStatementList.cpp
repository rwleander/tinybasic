//  testStatementList.cpp - test code for objStatementList

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "objStatementList.h"
#include "objStatement.h"

int main() {
	objStatementList lst;
  
//  test begin  method

  printf("Testing begin method\n");
  lst.begin();
  assert(lst.statementList[0] == 0);
  assert(lst.statementList[MAX_LINES - 1] == 0);  
  assert (lst.count == 0);
  
// done

  printf("Tests complete\n");
  return 0;
}
