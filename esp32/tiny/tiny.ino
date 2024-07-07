//  tiny basic for ESP32

#include <hardwareserial.h>

#include "objStatement.h"
#include "objStatementList.h"
#include "objRuntime.h"
#include "objTextBuffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// functions

void upshift(char* buff, int bufflen);
void doCommand(char* buff);
void listCode();
void checkHeap();

//  globals

objStatementList codeList;
objRuntime runtime;
objTextBuffer textWork;
int startHeap;

//  setup

void setup() {  
  Serial.begin(115200);  
  Serial.printf("Tiny Basic\n");
  Serial.printf(">");

  codeList.begin();
  runtime.begin();
  startHeap = ESP.getFreeHeap();
}

//  loop read console and do command

void loop() {
  char txt[100];
  char buff[100];
  int n = 0;
  int bufflen = 0;
  
strcpy(txt, "");
strcpy(buff, "");
if (Serial.available()) {
  n = Serial.readBytes(txt, 100);
  textWork.add(txt, n);
}

if (textWork.available == true) {
	bufflen = textWork.getText(buff);	
}

  if (bufflen > 0) {
    upshift(buff, bufflen);
    Serial.printf("%s\n", buff);

    doCommand(buff);
    Serial.printf(">");
      }
}

//  upshift char array

void upshift(char* buff, int bufflen) {
  for (int i=0; i<bufflen; i++) {    
      if ((buff[i] >= 'a') && (buff[i] <= 'z')) {
         buff[i] = buff[i] + 'A' - 'a';
      }
	  
	  if ((buff[i] == '\n') || (buff[i] == '\r')) {
		  buff[i] = '\0';
	  }	  
  }
  
  }

//  process command

void doCommand(char* buff) {
  objStatement validator;
 
 if (strcmp (buff, "") == 0) {
	 return;
 }
 
  if (strcmp(buff, "NEW") == 0) {
    codeList.clear();
    Serial.printf("Ok\n");
    return;
  }

  if (strcmp(buff, "LIST") == 0) {
    listCode();
    return;
  }

if (strcmp(buff, "RUN") == 0) {
	if (codeList.count == 0) {
		Serial.printf("Nothing to run\n");
		return;
	}
	
	runtime.run(&Serial, codeList);	
	return;
}

//  show memory

  if (strcmp(buff, "MEM") == 0) {
    checkHeap();
    return;
  }

//  add a line of code

  if (validator.isValid(buff) == 1) {
    objStatement* stmt = new objStatement(buff);
    codeList.add(stmt);
    Serial.printf("Ok\n");
    return;
  }
  
  Serial.printf("Unknown command\n");
}

//  list the program codeList

void listCode() {
  objStatement* stmt;

//  if no code, say sopen

  if (codeList.count == 0) {
    Serial.printf("Nothing to list\n");
    return;
  }

//  otherwise, list the code

  for (int i=0; i<codeList.count; i++){    
    Serial.printf("%d %s\n", codeList.getSequence(i), codeList.getText(i));
  }

  Serial.printf("Ok\n");
}

//  display current heap size

void checkHeap() {
  Serial.print("Heap: ");
  Serial.println(startHeap - ESP.getFreeHeap());
}
