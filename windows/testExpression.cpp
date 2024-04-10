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
  
  printf("Testing copy method\n");
  char* values1[] = {"1", "+", "2"};
  expr.copy(values1, 0, 2);
  assert(expr.count == 3);
  assert(strcmp(expr.tokens[0], "1") == 0);
  assert(strcmp(expr.tokens[1], "+") == 0);
  assert(strcmp(expr.tokens[2], "2") == 0);
  
  
  //  done
  
  printf("Done\n");
    return 0;
}
