//  objVariables.cpp - container for variables
//
//  variables must be single letters A through Z
//  vars array holds the values with vars[0] for A, vars[25] for Z
//


#include "objVariables.h"

//  begin - initialize object

void objVariables::begin() {
	  clear();
}

//  begin - initialize variables

void objVariables::clear() {
  for (int i=0; i<26; i++)
    values[i] = 0.0;
}

//  get value of variable

float objVariables::getVariable(char v) {
  int i = getIndex(v);
if (i >= 0) 
  return values[i];
else
return 0.0;
}

//  set variable to value_comp

void objVariables::setVariable(char v, float n) {
	  int i = getIndex(v);
	  if (i >= 0) values[i] = n;
}

//  get index for variable 
//  ie.  A = 0,  Z = 25

int objVariables::getIndex(char v) {
  if (v < 'A') return -1;
if (v > 'Z') return -1;
return v - 'A';  
}
