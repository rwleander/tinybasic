//  test random number generator

#include <string.h>
#include <stdio.h>

#include "objRandom.h"


int main() {
objRandom rnd;

//  print some random numbers

printf("Random numbers\n");

for (int i=0; i<5; i++) {
	printf("%f\n", rnd.getNext());
	printf("%f\n", rnd.getNext());
}
//  done

printf("tests complete\n");
return 0;
}
