//  testVariables.cpp - test code for objVariables

#include <stdio.h>
#include <assert.h>
#include "objVariables.h"

int main() {
  objVariables vars;
  
  //  test begin
  
  printf("Testing begin method");
    vars.begin();
	assert (vars.values[0] == 0.0);
	assert (vars.values[13] == 0.0);
	assert (vars.values[25] == 0.0);

// done
	
	printf("Tests complete");
	return 0;
}
