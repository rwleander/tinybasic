//  objLoader.h - methods to load and save programs

#ifndef __objLoader
#define __objLoader

#include "objStatementList.h"

class objLoader {
public:  
  char fileName[50];
  char msg[100];
  
  objLoader();
  bool loadFile(char* fname, objStatementList &codeList);
  bool saveFile(char* fname, objStatementList &codeList);
  bool buildFileName(char* fName);
};

#endif