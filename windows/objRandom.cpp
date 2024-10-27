//  random number generatr
//  two different versions for windows and esp32

//  code copied from stack overflow

#include "objRandom.h"
// constructor

objRandom::objRandom() {
	srand (static_cast <unsigned> (time(0)));
}

//  get next random number

float objRandom::getNext() {
return   static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
}
