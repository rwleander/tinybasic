//  tiny basic for ESP32

#include <hardwareserial.h>

#include "objStatement.h"
#include "objStatementList.h"
#include "objRuntime.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// functions

void upshift(char* buff, String* txt);
void doCommand(char* buff);
void listCode();
void checkHeap();

//  globals

objStatementList codeList;
objRuntime runtime;
int startHeap;

//  setup

void setup() {
  //M5.begin();
  //M5.Lcd.setRotation(3);
  //M5.Lcd.setCursor(0, 30, 4);
  //M5.Lcd.println("Tiny Basic");

  Serial.begin(115200);
  Serial.printf(">");

  codeList.begin();
  runtime.begin();
  startHeap = ESP.getFreeHeap();
}

//  loop read console and do command

void loop() {
  String txt;
  char buff[100];

  txt = Serial.readStringUntil('\n');

  if (txt.length() > 0) {
    upshift(buff, &txt);
    Serial.printf("%s\n", buff);

    doCommand(buff);
    Serial.printf(">");
      }
}

//  convert string to char array and upshift text

void upshift(char* buff, String* txt) {
  for (int i=0; i<100; i++) {
    buff[i] = '\0';

    if (i < txt->length() - 1) {
      if ((txt->charAt(i) >= 'a') && (txt->charAt(i) <= 'z')) {
         buff[i] = txt->charAt(i) + 'A' - 'a';
      }
      else {
        if (txt->charAt(i) != '\n') {
          buff[i] = txt->charAt(i);
        }
      }
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
