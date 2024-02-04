//  test objVariables with m5 stick

#include <M5StickC.h>
#include "objVariables.h"

objVariables vars;

//  setup

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.setCursor(0, 30, 4);
  M5.Lcd.println("Tiny Basic");
  
  Serial.begin(115200);
  
  vars.setVariable('A', 10.0);
  vars.setVariable('B', 20.0);
  vars.setVariable('M', 30.0);
  vars.setVariable('Z', 40.0);  
}

//  loop look for button press

void loop() {
	  float n;
	  	
	 if (M5.BtnA.read() == 1) {
		   n = vars.getVariable('M');
    Serial.println(n);
  }

  m5.update();
  delay(10);
  
}
