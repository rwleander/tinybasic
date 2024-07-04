//  testTextBuffer.cpp - test code for buffered input_iterator
//    note: this code is only used in the arduino version

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "objTextBuffer.h"

int main() {
  objTextBuffer textData;

//  test default constructor

  printf("Testing default constructor method\n");
  objTextBuffer textData1;
  assert (textData1.start == 0);
  assert (textData1.end == 0);
  assert (textData1.available == false);

//  test first add  

  printf("Testing initial add\n");
  textData.add("ABCDE", 5);  
  assert(textData.textWork[0] == 'A');
  assert(textData.textWork[4] == 'E');
  assert(textData.textWork[5] == '\0');
  assert (textData.start == 0);
  assert (textData.end == 5);
  assert (textData.available == false);



//  done

printf("Tests complete\n");  
}
