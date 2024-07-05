//  objTextBuffer.h - hold and split text input into statements
//    note: this code is only used in the arduino version

#ifndef __objTextBuffer
#define __objTextBuffer

#include "constants.h"

#define MAX_WORK 500

class objTextBuffer {
public:  
  char textWork[MAX_WORK];
int start = 0;
int end = 0;
bool available = false;

  objTextBuffer();
    void clear();
  void add (char* buff, int n);
  int getText(char* buff);
  bool checkAvailable();

   
};

#endif
