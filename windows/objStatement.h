//  objStatement.h - container to hold one line of basic code

#ifndef __objStatement
#define __objStatement

#define TRUE 1
#define FALSE 0

class objStatement {
public:
  int sequence;
  char text[60];

  objStatement();
  objStatement(char* line);
  void setLine(char* line);
  int getLine(char* line);
   bool isValid(char* line);
};

#endif