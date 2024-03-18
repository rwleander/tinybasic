//  objStatement.h - container to hold one line of basic code

#ifndef __objStatement
#define __objStatement

class objStatement {
public:
  int sequence;
  char text[60];

  objStatement();
  objStatement(char* line);
  void setLine(char* line);
  int getLine(char* line);
};

#endif