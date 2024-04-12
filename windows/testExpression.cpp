//  test expression parser and calculator

#include "objExpression.h"
#include "objRuntime.h"
#include "objVariables.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

int main() {
  objExpression expr;
  
  printf("Testing expressions\n");
  
  //  test clear method
  
  printf("Testing clear method\n");
  expr.clear();
  assert(expr.count == 0);
  assert(expr.tokens[0] == 0);
  assert(expr.tokens[5] == 0);
  
  //  test copy method
  
  printf("Testing simple copy\n");
  char* test1[] = {"1", "+", "2"};
  expr.copy(test1, 0, 2);
  assert(expr.count == 3);
  assert(strcmp(expr.tokens[0], "1") == 0);
  assert(strcmp(expr.tokens[1], "+") == 0);
  assert(strcmp(expr.tokens[2], "2") == 0);
  
  printf("Testing embedded copy\n");
  char* test2[] = {"LET", "A", "=", "A", "+", "B", "-", "C"};
  expr.copy(test2, 3, 7);  
  assert(expr.count == 5);
  assert(strcmp(expr.tokens[0], "A") == 0);
  assert(strcmp(expr.tokens[1], "+") == 0);
  assert(strcmp(expr.tokens[2], "B") == 0);
  assert(strcmp(expr.tokens[3], "-") == 0);
  assert(strcmp(expr.tokens[4], "C") == 0);
    
  //  test for valid operators
  
  printf("Testing isOperator method\n");
  assert(expr.isOperator("*") == TRUE);
  assert(expr.isOperator("0") == FALSE);
  
  //  test get precedence
  
  printf ("Testing getPrecedence method\n");
  assert(expr.getPrecedence("/") == 3);
  assert(expr.getPrecedence("0") == -1);

//  test load rpn method\n");

printf("Testing load rpn method\n");
char* test3[] = {"2", "*", "3", "+", "4"};
expr.copy(test3, 0, 4);
assert(expr.count == 5);
expr.loadRpn();
assert(strcmp(expr.rpn[0], "2") == 0);
assert(strcmp(expr.rpn[1], "3") == 0);
assert(strcmp(expr.rpn[2], "*") == 0);
assert(strcmp(expr.rpn[3], "4") == 0);
assert(strcmp(expr.rpn[4], "+") == 0);


printf("Testing load rpn method again\n");
char* test4[] = {"2", "+", "3", "*", "4"};
expr.copy(test4, 0, 4);
assert(expr.count == 5);
expr.loadRpn();
assert(strcmp(expr.rpn[0], "2") == 0);
assert(strcmp(expr.rpn[1], "3") == 0);
assert(strcmp(expr.rpn[2], "4") == 0);
assert(strcmp(expr.rpn[3], "*") == 0);
assert(strcmp(expr.rpn[4], "+") == 0);


  
  //  done
  
  printf("Done\n");
    return 0;
}
