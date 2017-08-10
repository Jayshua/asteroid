#include <stdio.h>
#include <stdlib.h>
#include "assertion.h"


void assertFun(bool assertion, char *p_file, const char *p_function, int line_number) {
   if (assertion == false) {
      printf("\nAssertion failed at %s:%d (%s)", p_file, line_number, p_function);
      exit(-1);
   }
}
