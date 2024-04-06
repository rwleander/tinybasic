//  testStatementList.cpp - test code for objStatementList

#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "objStatementList.h"
#include "objStatement.h"

int main() {
  objStatementList lst;
  char buff[100];
  int n;

//  test begin  method

  printf("Testing begin method\n");
  lst.begin();
  assert(lst.statementList[0] == 0);
  assert(lst.statementList[MAX_LINES - 1] == 0);
  assert (lst.count == 0);

//  test add method 

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

//  test remove method

  printf("Testing remove   method\n");
  n = lst.find(20);
  assert(n == 2);
  lst.remove(n);
  assert(lst.count == 4);
  assert(lst.statementList[1] == stmt1a);
  assert(lst.statementList[2] == stmt3a);

//  test getSequence and getText methods

printf("Testing getSequence and getText methods\n");
assert(lst.getSequence(0) == 10);
assert (strcmp(lst.getText(0), "LET A = 1") == 0);

//  test the clear method

  printf("Testing clear   method\n");
  lst.clear();
  assert(lst.count == 0);
  assert(lst.statementList[0] == 0);


//  final test

  printf("Final test\n");
  printf("add statements\n");
  objStatement* stmt10 = new objStatement("10 LET A = 1");
  objStatement* stmt20 = new objStatement("20 LET B = 2");
  objStatement* stmt30 = new objStatement("30 LET C = 3");
  objStatement* stmt40 = new objStatement("40 PRint C");
  lst.add(stmt20);
  lst.add(stmt40);
  lst.add(stmt30);
  lst.add(stmt10);
  assert(lst.statementList[0] == stmt10);
  assert(lst.statementList[1] == stmt20);
  assert(lst.statementList[2] == stmt30);
  assert(lst.statementList[3] == stmt40);
  assert(lst.count == 4);

//  replace a line

  printf("replace a line\n");
  objStatement* stmt30a = new objStatement("30 LET C = A + b");
  lst.add(stmt30a);
  assert(lst.statementList[1] == stmt20);
  assert(lst.statementList[2] == stmt30a);
  assert(lst.statementList[3] == stmt40);
  assert(lst.count == 4);

//  delete a line

  printf("Delete a line\n");
  objStatement* stmt20a = new objStatement("30");
  lst.add(stmt20a);
  assert(lst.statementList[1] == stmt20);
  assert(lst.statementList[2] == stmt40);
  assert(lst.count == 3);

//  finally clear

  printf("Clear the list\n");
  lst.clear();
  assert(lst.count == 0);

//  test exceptions
//  over-fill the list

printf("Testing overflow handler\n");
n = 10;
while (n < 300) {
	  sprintf(buff, "%d LET A = 0", n);	  
	  lst.add(new objStatement(buff));
	  n++;
}
assert(lst.count == MAX_LINES);

// done

  printf("Tests complete\n");

  return 0;
}
