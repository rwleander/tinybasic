//  objTextBuffer.cpp - hold and split text input into statements
//    note: this code is only used in the arduino version

#include "objTextBuffer.h"

#include <string.h>
#include <stdio.h>

//  default constructor

objTextBuffer::objTextBuffer() {
  clear();
}

//  clear variables

void objTextBuffer::clear() {
	  for (int i=0; i<MAX_WORK; i++) textWork[i] = '\0';
	  start = 0;
	  end = 0;
	  available = false;
}

//  add text to the work area

void objTextBuffer::add(char* buff, int n) {
	  int i = 0;
	  while (i < n) {
		  textWork[end] = buff[i];
		  if (buff[i] == '\n') {
			  available = true;
			  end++;
			  textWork[end] = '\0';
		  }
		  
		  i++;
		  end++;		  
	  }
		  
		  textWork[end] = '\0';
		  end++;
	  }
	  
	  //  get availabel text
	  
	  int objTextBuffer::getText(char* buff) {		  
	  
	  //  if no data, return 0
	  
		  if ((start == end) || (available == false)) {
			  buff[0] = '\0';
			  return 0;
		  }

//  copy characters until new line

int n = 0;
while (textWork[start] != '\n') {
	if (textWork[start] != '\0') {
	  buff[n] = textWork[start];
	  n++;
	}
	
	start++;
}

//  copy newline and trailing 0

buff[n] = textWork[start];
buff[n+1] = '\0';
n++;
start += 2;
available = false;
return n;
	  }