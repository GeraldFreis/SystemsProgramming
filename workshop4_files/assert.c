#include <stdio.h>
#include <stdlib.h>
#include "assert.h"

void assert(int ok, char* msg)
{
  if( ok ){
    return;
  }

  //Assertion failure
  fprintf(stderr,"Assert: %s. ok=%d\n",msg,ok);
  exit(1);
}
