//  objStatement.h - container to hold one line of basic code

#ifndef __objStatement
#define __objStatement

#include "constants.h"

class objStatement {
public:
  int sequence;
  char text[MAX_STRING];

  objStatement();
  objStatement(char* line);
  void setLine(char* line);
  int getLine(char* line);
   bool isValid(char* line);
};

#endif