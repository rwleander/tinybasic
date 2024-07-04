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
		  }
		  
		  i++;
		  end++;		  
	  }
		  
		  textWork[end] = '\0';
	  }
	  