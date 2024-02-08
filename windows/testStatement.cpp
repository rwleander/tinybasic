//  testStatement.cpp - test code for objStatement

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "objStatement.h"

int main() {
  objStatement stmt;
  
  //  test default constructor
  
  printf("Testing default constructor method\n");
  objStatement stmt1;
  assert (stmt1.sequence == 0);
  assert (strcmp(stmt1.text, "") == 0);

//  test setLine method\n
  
  printf("Testing set line method");  
  stmt1.setLine("10 LET A = 10");
  assert (stmt1.sequence == 10);
assert (strcmp(stmt1.text, "LET A = 10") == 0);

//  test alternate constructor
  
  printf("Testing alternate  constructor method\n");
  objStatement* stmt2 = new objStatement("120  LET B = 20");
  assert (stmt2->sequence == 120);
  assert (strcmp(stmt2->text, "LET B = 20") == 0);

//  test getLine function
  
  printf("Testing get line function method\n");  
  char line[65];
  int n   = stmt2->getLine(line);  
  assert(strcmp(line, "120 LET B = 20") == 0);
	
// done
	
	printf("Tests complete\n");
	return 0;
}
