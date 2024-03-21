//  tiny basic interpreter - main program

#include"objStatementList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  globals

objStatementList codeList;

//  main
int main() {
	char buff[100];
	int buffLen;
	bool quitFlag = 0;
	
		//  title
	
	printf("Tiny Basic for the ESP32\n");
	
	//  command loop
	
	while (quitFlag == 0) {
		strcpy(buff, "");
		printf(">");
		scanf("%s", buff);
		
		if (strcmp(buff, "QUIT") == 0) {
			quitFlag = 1;
		}
		
	}

printf("Bye\n");
return 0;
}