//  testVariables.cpp - test code for objVariables

#include <stdio.h>
#include <assert.h>
#include "objVariables.h"

int main() {
objVariables vars;

//  test begin

printf("Testing begin method\n");
vars.begin();
assert (vars.values[0] == 0.0);
assert (vars.values[13] == 0.0);
assert (vars.values[25] == 0.0);

// test clear

printf("Testing clear  method\n");
vars.values[5] = 10.0;
vars.clear();
assert (vars.values[5] == 0.00);//  test getIndex

printf("Testing getIndex  method\n");
assert(vars.getIndex('A') == 0);
assert(vars.getIndex('F') == 5);
assert(vars.getIndex('Z') == 25);
assert(vars.getIndex('a') == -1);

//  test setVariable method

printf("Testing setVariable method\n");
vars.setVariable ('A', 10.0);
vars.setVariable('J', 20.0);
vars.setVariable('Z', 30.0);
assert (vars.values[0] == 10.0);
assert(vars.values[9] == 20.0);
assert(vars.values[25] == 30.0);

// test getVariable method

printf("Testing getVariable method\n");assert (vars.getVariable('A') == 10.0);
assert(vars.getVariable('J') == 20.0);
assert(vars.getVariable('Z') == 30.0);

// done

printf("Tests complete\n");
return 0;
}
