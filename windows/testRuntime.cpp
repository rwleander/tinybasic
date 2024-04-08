//  test runtime class

#include "objRuntime.h"
#include "objStatement.h"
#include "objStatementList.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

int main() {
  objRuntime runtime;
  char buff[100];
  int n;
  bool ok;
  
  printf("Testing runtime\n");
  
  //  test find token methods
  //  simple test
  
  printf("Testing find tokens method - print a\n");
  n = runtime.findTokens("PRINT A");
  assert(runtime.count == 2);
  assert(strcmp(runtime.tokens[0], "PRINT") == 0);
assert(strcmp(runtime.tokens[1], "A") == 0);
assert (n == 2);

//  test get tokens with commas

printf("Testing get token method with commas\n");
  n = runtime.findTokens("PRINT A, B");  
  assert(runtime.count == 4);
  assert(strcmp(runtime.tokens[0], "PRINT") == 0);
assert(strcmp(runtime.tokens[1], "A") == 0);
assert(strcmp(runtime.tokens[2], ",") == 0);
assert(strcmp(runtime.tokens[3], "B") == 0);

//  test more complex expression

printf("Testing get token method with parenthesis\n");
  n = runtime.findTokens("LET A = B * (C + D)");  
  assert(runtime.count == 10);
  assert(strcmp(runtime.tokens[0], "LET") == 0);
assert(strcmp(runtime.tokens[1], "A") == 0);
assert(strcmp(runtime.tokens[2], "=") == 0);
assert(strcmp(runtime.tokens[3], "B") == 0);
assert(strcmp(runtime.tokens[4], "*") == 0);
assert(strcmp(runtime.tokens[5], "(") == 0);
assert(strcmp(runtime.tokens[6], "C") == 0);
assert(strcmp(runtime.tokens[7], "+") == 0);
assert(strcmp(runtime.tokens[8], "D") == 0);
assert(strcmp(runtime.tokens[9], ")") == 0);

//  test print function

printf("Testing print with one number\n");
n = runtime.findTokens("PRINT 5");
assert(n == 2);
ok = runtime.print(buff);
assert(ok == TRUE);
assert (strcmp(buff, "5") == 0);

printf("Testing print with one literal\n");
n = runtime.findTokens("PRINT \"This is a test\"");
assert(n == 2);
ok = runtime.print(buff);
assert(ok == TRUE);
assert (strcmp(buff, "This is a test") == 0);

//  done

  printf("Tests complete\n");
  return 0;
}
