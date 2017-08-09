#include <stdio.h>
#include <stdlib.h>
#include "assertion.h"


void assertFun(bool assertion, char *p_message, char *p_file, const char *p_function, int line_number) {
   if (assertion == false) {
      printf("\nError at %s:%d (%s)", p_file, line_number, p_function);
      printf("\n%s", p_message);
      printf("\nThe program will now exit.");
      exit(-1);
   }
}
