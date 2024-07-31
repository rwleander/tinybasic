//  tiny basic interpreter - main program

#include"objStatementList.h"
#include "objRuntime.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  function prototypes

void upshift(char* buff);
void doCommand(char* buff);
void listCode();

//  globals

objStatementList codeList;
objRuntime runtime;
bool quitFlag = FALSE;

//  main
int main() {
  char buff[100];

//  title

  printf("Tiny Basic for the ESP32\n");

codeList.begin();
runtime.begin();

//  command loop

  while (quitFlag == FALSE) {
    strcpy(buff, "");
    printf(">");
    fgets(buff, 99, stdin);

    upshift(buff);
    doCommand(buff);
  }

//  end program

  printf("Bye\n");
  return 0;
}

//  upshift textattr

void upshift(char* buff) {
  for (int i=0; i<strlen(buff); i++) {
    if ((buff[i] >= 'a') && (buff[i] <= 'z')) {
      buff[i] = buff[i] + 'A' - 'a';
    }

    if (buff[i] == '\n') {
      buff[i] = '\0';
    }
  }
}

//  process command

void doCommand(char* buff) {
  objStatement validator;
 
  if (strcmp(buff, "NEW") == 0) {
    codeList.clear();
    printf("Ok\n");
    return;
  }

  if (strcmp(buff, "LIST") == 0) {
    listCode();
    return;
  }

if (strcmp(buff, "RUN") == 0) {
	if (codeList.count == 0) {
		printf("Nothing to run\n");
		return;
	}
	
if (	runtime.run(codeList) != TRUE) {
	printf("%d %s\n", runtime.sequence, runtime.text);
	printf("%s\n", runtime.msg);
}	

	return;
}
	
  if (strcmp(buff, "QUIT") == 0) {
    quitFlag = TRUE;
    return;
  }

  if (validator.isValid(buff) == 1) {
    objStatement* stmt = new objStatement(buff);
    codeList.add(stmt);
    printf("Ok\n");
    return;
  }
  else {
	  printf ("Bad statement\n");
	  return;
  }
  printf("Unknown command\n");
  
}

//  list the program codeList

void listCode() {
  objStatement* stmt;

//  if no code, say so

  if (codeList.count == 0) {
    printf("Nothing to list\n");
    return;
  }

//  otherwise, list the code

  for (int i=0; i<codeList.count; i++){    
    printf("%d %s\n", codeList.getSequence(i), codeList.getText(i));
  }

  printf("Ok\n");
}
