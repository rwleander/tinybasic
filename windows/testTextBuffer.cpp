//  testTextBuffer.cpp - test code for buffered input_iterator
//    note: this code is only used in the arduino version

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "objTextBuffer.h"

int main() {
  objTextBuffer textData;
char buff[100];
int n;

//  test default constructor

  printf("Testing default constructor method\n");  
  assert (textData.start == 0);
  assert (textData.end == 0);
  assert (textData.available == false);

//  test first add  

  printf("Testing initial add\n");
  textData.add("ABCDE", 5);  
  assert(strcmp(textData.textWork, "ABCDE") == 0);
  assert (textData.start == 0);
  assert (textData.end == 6);
  assert (textData.available == false);

//  add more textData

  printf("Testing second add\n");
  textData.add("FG\n", 3);        
  assert (textData.start == 0);
  assert (textData.end == 11);
  assert (textData.available == true);

//  test getText

  printf("Testing get text\n");
  n = textData.getText(buff);    
  assert(strcmp(buff, "ABCDEFG\n") == 0);
  assert(n == 8);
  assert (textData.start == 10);
  assert (textData.end == 11);
  assert (textData.available == false);

//  add another line
  printf("Testing third add\n");
  textData.add("more data\n", 10);    
  assert (textData.start == 10);
  assert (textData.end == 23);
  assert (textData.available == true);

//  get third add data

  printf("Testing second get text\n");
  n = textData.getText(buff);    
  assert(strcmp(buff, "more data\n") == 0);
  assert(n == 10);
  assert (textData.start == 22);
  assert (textData.end == 23);
  assert (textData.available == false);



//  done

printf("Tests complete\n");  
}
