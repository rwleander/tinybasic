//  test objVariables with m5 stick

#include <M5StickC.h>
#include <assert.h>
#include "objStatement.h"
#include "objStatementList.h"

// functions

void runTest();

//  globals

objStatementList lst;

//  setup

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.setCursor(0, 30, 4);
  M5.Lcd.println("Tiny Basic");
  
  Serial.begin(115200);  
  lst.begin();
}

//  loop look for button press

void loop() {  	  	
	 if (M5.BtnA.read() == 1) {		   
    runTest();
  }

  m5.update();
  delay(250);  
}
//  run a test
void runTest() {
	int free1 = ESP.getFreeHeap();
	
  Serial.println("add statements");
  objStatement* stmt10 = new objStatement("10 LET A = 1");
  objStatement* stmt20 = new objStatement("20 LET B = 2");
  objStatement* stmt30 = new objStatement("30 LET C = 3");
  objStatement* stmt40 = new objStatement("40 PRint C");
  lst.add(stmt20);
  lst.add(stmt40);
  lst.add(stmt30);
  lst.add(stmt10);
  assert(lst.statementList[0] == stmt10);
  assert(lst.statementList[1] == stmt20);
  assert(lst.statementList[2] == stmt30);
  assert(lst.statementList[3] == stmt40);
  assert(lst.count == 4);

//  replace a line

  Serial.println("replace a line");
  objStatement* stmt30a = new objStatement("30 LET C = A + b");
  lst.add(stmt30a);
  assert(lst.statementList[1] == stmt20);
  assert(lst.statementList[2] == stmt30a);
  assert(lst.statementList[3] == stmt40);
  assert(lst.count == 4);

//  delete a line

  Serial.println("Delete a line");
  objStatement* stmt20a = new objStatement("30");
  lst.add(stmt20a);
  assert(lst.statementList[1] == stmt20);
  assert(lst.statementList[2] == stmt40);
  assert(lst.count == 3);

//  finally clear

  Serial.println("Clear the list");
  lst.clear();
  assert(lst.count == 0);

//  check for memory leaks

int free2 = ESP.getFreeHeap();
if (free1 < free2) {
	Serial.print("Possible memory leak - ");
	Serial.println(free2 - free1);
	
}

// done

  Serial.println("Tests complete");
}
