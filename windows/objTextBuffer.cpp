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
	
	//  if past end, compress
	if ((end + n + 5) >= MAX_WORK) {
		compress();
	}
	
	//  copy data to textWork
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
	  
		  if ((start + 1 >= end) || (available == false)) {
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

//  if we still have text, see if there's another line feed

if (start + 1 < end) {
	available = checkAvailable();
}

return n;
	  }
	  
	  
	  //  see if there's another line feed
	  
	  bool objTextBuffer::checkAvailable() {
		  int i = start;
		  while (i < end) {
			  if (textWork[i] == '\n') return true;
			  i++;
		  }
		  
		  return false;
	  }
	  
	  
	  //  shift data back to start of text buffer
	  
	  void objTextBuffer::compress() {
		  
		  //  copy data to start of textWork
		  
		  int i = 0;
		  while (start < end) {
			  textWork[i] = textWork[start];
			  i++;
			  start++;
		  }
		  
		  //  reset pointers
		  
		  start = 0;
		  end = i;
		  
		  //  clear remaining buffer
		  
	  while (i < MAX_WORK) {
		  textWork[i] = '\0';
		  i++;
	  }
	  
	  }
	  