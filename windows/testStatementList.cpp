//  testStatementList.cpp - test code for objStatementList

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "objStatementList.h"
#include "objStatement.h"

int main() {
	objStatementList lst;
	int n;
	
  
//  test begin  method

  printf("Testing begin method\n");
  lst.begin();
  assert(lst.statementList[0] == 0);
  assert(lst.statementList[MAX_LINES - 1] == 0);  
  assert (lst.count == 0);
  
  //  test add methodprintf("Testing begin method\n");
  
  printf("Testing initial add  method\n");
  objStatement* stmt1 = new objStatement("10 LET A = 1");
  objStatement* stmt2 = new objStatement("20 LET B = 2");
  objStatement* stmt3 = new objStatement("30 LET C = 3");
  objStatement* stmt4 = new objStatement("40 PRINT A + B +C");
  n = lst.add(stmt1);
  n = lst.add(stmt2);
  n = lst.add(stmt3);
  n = lst.add(stmt4);
  assert(lst.statementList[0] == stmt1);
  assert(lst.statementList[1] == stmt2);
  assert(lst.statementList[2] == stmt3);
  assert(lst.statementList[3] == stmt4);
  assert (lst.count == 4);
  assert (n == 4);

//  test find method on matching line number

  printf("Testing find    method with exact match\n");
  n = lst.find(30);
  assert(n == 2);

//  test find with missing statement 

  printf("Testing find    method with missing statement\n");
  n = lst.find(15);
  assert(n == 1);

//  test replace method

  printf("Testing replace method\n");
  n = lst.find(30);
  assert(n == 2);
  objStatement* stmt3a = new objStatement("30 LET C = 30");  
  lst.replace(stmt3a, n);  
  assert(lst.count == 4);
  assert(lst.statementList[1] == stmt2);
  assert(lst.statementList[2] == stmt3a);
  assert(lst.statementList[3] == stmt4);
  
//  test insert method
  printf("Testing insert  method\n");
  n = lst.find(15);
  assert(n == 1);
  objStatement* stmt1a = new objStatement("15 LET A = A * 2");
  lst.insert(stmt1a, n);  
  assert(lst.count == 5);
  assert(lst.statementList[0] == stmt1);
  assert(lst.statementList[1] == stmt1a);
  assert(lst.statementList[2] == stmt2);
  
  


// done

  printf("Tests complete\n");
  return 0;
}
