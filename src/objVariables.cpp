//  objVariables.cpp - container for variables
//
//  variables must be single letters A through Z
//  vars array holds the values with vars[0] for A, vars[25] for Z
//


#include "objVariables.h"

//  begin - initialize variables

void objVariables::begin() {
  for (int i=0; i<26; i++)
    values[i] = 0.0;
}

