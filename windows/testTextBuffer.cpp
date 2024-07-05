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

//  test get when available is false
  printf("Testing get when not available\n");
  n = textData.getText(buff);    
  assert(strcmp(buff, "") == 0);
  assert (n == 0);
  
  //  test add and get with two lines

  printf("Testing add with two lines\n");
  textData.add("line1\nline2\n", 12); 
  assert (textData.available == true);
  
  n = textData.getText(buff);
  assert (n == 6);
  assert (strcmp(buff, "line1\n") == 0);
  assert (textData.available == true);
  
  n = textData.getText(buff);
  assert (n == 6);
  assert (strcmp(buff, "line2\n") == 0);
  assert (textData.available == false);
  
  //  test compress method 
  
  printf("testing compress method\n");
  textData.clear();
  textData.start = 400;
  textData.end = 400;
  textData.add("abcdef", 6);  
  assert(textData.start == 400);
  assert(textData.end == 407);
  assert(textData.available == false);
  
  textData.compress();      
  assert(strcmp(textData.textWork, "abcdef") == 0);
  assert(textData.start == 0);
  assert(textData.end == 7);
  assert(textData.available == false);
  
//  final test = add and read text to force compress

textData.clear();
for (int i=0; i<75; i++) {
textData.add("123456789\n", 10);
assert(textData.available == true);

n = textData.getText(buff);
assert(strcmp(buff, "123456789\n") == 0);
assert(n == 10);
}

//  done

printf("Tests complete\n");  
}
