#pragma once
#include <stdbool.h>

// Assert that a value holds, printing an error message and exiting if not.
#define assertion(asdf_assertion, asdf_message) assertFun(asdf_assertion, asdf_message, __FILE__, __FUNCTION__, __LINE__)

// Ignore this function. Use the macro instead.
void assertFun(bool assertion, char *p_message, char *p_file, const char *p_function, int line_number);