//  random number generator
//  need alternate files for windows and esp32

#ifndef __objRandom
#define __objRandom

#include <stdlib.h>
#include <time.h>


class objRandom {
public:
  objRandom();
  float getNext();
  };

#endif
