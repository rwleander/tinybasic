//  test expression parser and calculator

#include "objExpression.h"
#include "objRuntime.h"
#include "objVariables.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

int main() {
  objExpression expr;
  float f = 0.0;
  
//  test cases

char* test1[] = {"1", "+", "2"};  
char* test2[] = {"LET", "A", "=", "A", "+", "B", "-", "C"};
char* test3[] = {"2", "*", "3", "+", "4"};
char* test4[] = {"2", "+", "3", "*", "4"};
char* test5[] = {"2", "*", "3", "+", "4", "*", "5"};
char* test6[] = {"(", "2", "+", "3", ")", "*", "(", "4", "+", "5", ")"};


//  start tests

  printf("Testing expressions\n");
  
  //  test clear method
  
  printf("Testing clear method\n");
  expr.clear();
  assert(expr.count == 0);
  assert(expr.tokens[0] == 0);
  assert(expr.tokens[5] == 0);
  
  //  test copy method
  
  printf("Testing simple copy\n");  
  expr.copy(test1, 0, 2);
  assert(expr.count == 3);
  assert(strcmp(expr.tokens[0], "1") == 0);
  assert(strcmp(expr.tokens[1], "+") == 0);
  assert(strcmp(expr.tokens[2], "2") == 0);
  
  printf("Testing embedded copy\n");  
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
expr.clear();
expr.copy(test3, 0, 4);
assert(expr.count == 5);
expr.loadRpn();
assert(strcmp(expr.rpn[0], "2") == 0);
assert(strcmp(expr.rpn[1], "3") == 0);
assert(strcmp(expr.rpn[2], "*") == 0);
assert(strcmp(expr.rpn[3], "4") == 0);
assert(strcmp(expr.rpn[4], "+") == 0);

//  calculate results

printf("Testing calcuate\n");
f = expr.calculate();
assert (f == 10);

//  second test

printf("Testing load rpn method again\n");
expr.copy(test4, 0, 4);
assert(expr.count == 5);
expr.loadRpn();
assert(strcmp(expr.rpn[0], "2") == 0);
assert(strcmp(expr.rpn[1], "3") == 0);
assert(strcmp(expr.rpn[2], "4") == 0);
assert(strcmp(expr.rpn[3], "*") == 0);
assert(strcmp(expr.rpn[4], "+") == 0);

//  calculate results

printf("Testing calcuate again\n");
f = expr.calculate();
assert (f == 14);

//  test longer expression

printf("Testing calc of longer expression\n");
expr.copy(test5, 0, 6);
assert(expr.count == 7);
expr.loadRpn();
assert(strcmp(expr.rpn[0], "2") == 0);
assert(strcmp(expr.rpn[1], "3") == 0);
assert(strcmp(expr.rpn[2], "*") == 0);
assert(strcmp(expr.rpn[3], "4") == 0);
assert(strcmp(expr.rpn[4], "5") == 0);
assert(strcmp(expr.rpn[5], "*") == 0);
assert(strcmp(expr.rpn[6], "+") == 0);

f = expr.calculate();
assert (f == 26);

//  test expression with parens

printf("Testing calc with parens\n");
expr.copy(test6, 0, 10);
assert(expr.count == 11);
expr.loadRpn();
assert(strcmp(expr.rpn[0], "2") == 0);
assert(strcmp(expr.rpn[1], "3") == 0);
assert(strcmp(expr.rpn[2], "+") == 0);
assert(strcmp(expr.rpn[3], "4") == 0);
assert(strcmp(expr.rpn[4], "5") == 0);
assert(strcmp(expr.rpn[5], "+") == 0);
assert(strcmp(expr.rpn[6], "*") == 0);

f = expr.calculate();
assert (f == 45);
  
  //  done
  
  printf("Done\n");
    return 0;
}