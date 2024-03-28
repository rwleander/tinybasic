//  test runtime class

#include "objRuntime.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

int main() {
  objRuntime runtime;
  int n;
  
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
  printf("%d\n", n);
  assert(runtime.count == 4);
  assert(strcmp(runtime.tokens[0], "PRINT") == 0);
assert(strcmp(runtime.tokens[1], "A") == 0);
assert(strcmp(runtime.tokens[2], ",") == 0);
assert(strcmp(runtime.tokens[3], "B") == 0);

//  done

  printf("Tests complete\n");
  return 0;
}
