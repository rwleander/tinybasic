//  test objVariables with m5 stick

#include <M5StickC.h>
#include "objStatement.h"

objStatement stmt;

//  setup

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.setCursor(0, 30, 4);
  M5.Lcd.println("Tiny Basic");
  
  Serial.begin(115200);
  
  stmt.setLine("120 LET A = 100");
}

//  loop look for button press

void loop() {
	  float n;
	  	
	 if (M5.BtnA.read() == 1) {		   
    Serial.println(stmt.sequence);
	Serial.println(stmt.text);
  }

  m5.update();
  delay(10);
  
}
