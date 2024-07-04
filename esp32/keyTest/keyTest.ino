//  keyTest.ino - tes keyInput class

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char txt[100];
bool hasData = false;

//  setup

void setup() {
	Serial.begin(115200);
	Serial.println("Ready");
	strcpy(txt, "");
}


//  loop

void loop() {
	checkInput();
	if (hasData ) {
		Serial.printf("found %d\n", strlen(txt));
		strcpy(txt, "");
		hasData = false;
	}
}

//  check for serial data

void checkInput() {
	char buff[100];
	int bufflen = 0;
		
	if (Serial.available()) {
		bufflen = Serial.readBytes(buff, 100);

if (bufflen > 0) {
	buff[bufflen] = '\0';
	strcpy (txt, buff);
	hasData = true;
}
		
	}
}
