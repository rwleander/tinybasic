//  objLoader.cpp - load and save program files

#include "objLoader.h"
#include "constants.h"

#include <string.h>
#include <stdio.h>

//  constructor

objLoader::objLoader() {
	  strcpy(fileName, "");
	  strcpy(msg, "");
}

//  load a file

bool objLoader::loadFile(char* fName, objStatementList &codeList) {
	  FILE* fl;
	  objStatement* stmt;
	  char buff[100];
	  
	  //  clear the list
	  codeList.clear();
	  
	  //  open the file
	  
	  buildFileName(fName);
	  fl = fopen(fileName, "r");
	  if (!fl) {
		  strcpy(msg, "cannot find file");
		  return false;
	  }
	  
	  //  load the file
	  //  note: need to remove trailing line feed from text string
	  
	  
	  while (fgets(buff, 100, fl) != NULL) {
		  buff[strlen(buff) - 1] = '\0';		  
		  stmt = new objStatement(buff);
		  codeList.add(stmt);
	  }
	  	  
	  //  close the file
	  
	  fclose(fl);
	  strcpy(msg, "");
	  return true;
}

//  save a file

bool objLoader::saveFile(char* fName, objStatementList &codeList) {  
  FILE* fl;
  char buff[100];
  int i = 0;
  
  //  if empty, say sopen
  if (codeList.count == 0) {
	  strcpy(msg, "No code");
	  return false;
  }
  
  //  set up the file name
  
  buildFileName(fName);
  
  //  open the file
  
  fl = fopen(fileName, "w");
  if (!fl) {
	  strcpy(msg, "cannot create file");
	  return false;
  }
  
  //  write the code
  
  for (i = 0; i < codeList.count; i++) {
	  sprintf(buff, "%d %s\n", codeList.getSequence(i), codeList.getText(i));	  
	  fprintf(fl, buff);
  }
  
  //  close the file
  
  fclose(fl);
  strcpy(msg, "");
  return true;
}

//  build the file name with path and extension

void objLoader::buildFileName(char* fName) {
	  strcpy(fileName, filePath);
	  strcat(fileName, fName);
	  strcat(fileName, fileExt);
}
