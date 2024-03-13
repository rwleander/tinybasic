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
  
  //  test add methodprintf("Testing begin method\n");
  
  printf("Testing initial add  method\n");
  objStatement* stmt1 = new objStatement("10 LET A = 1");
  lst.add(stmt1);
  assert(lst.statementList[0] == stmt1);
  assert (lst.count == 1);

// add second line to end of list  

  printf("Testing second  add  method\n");
  objStatement* stmt3 = new objStatement("30 LET C = 3");
  lst.add(stmt3);
  assert(lst.statementList[0] == stmt1);
  assert(lst.statementList[1] == stmt3);
  assert (lst.count == 2);

//  add line between other lines

  printf("Testing inserted  add  method\n");
  objStatement* stmt2 = new objStatement("20 LET B = 2");
  lst.add(stmt2);
  assert(lst.statementList[0] == stmt1);
  assert(lst.statementList[1] == stmt2);
  assert(lst.statementList[2] == stmt3);
  assert (lst.count == 3);
  
  
  
// done

  printf("Tests complete\n");
  return 0;
}
