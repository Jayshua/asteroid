#pragma once
#include <stdbool.h>

// GCC Flag that can be placed on function causing a warning when the function's return value isn't used
// Extra useful when that return value is an error code
#define MUST_USE_RETURN __attribute__ ((warn_unused_result))

// Return type for functions returning an error code.
// Should be used in conjunction with the MUST_USE_RETURN macro
typedef int ErrorCode;

// ErrorCode variants
#define SUCCESS                  0
#define ERR_SHADER_COMPILE       1 // Compiling a shader failed
#define ERR_PROGRAM_LINK         2 // Linking a shader program failed
#define ERR_SHADER_LOG_MALLOC    3 // Allocating memory for a shader compilation log failed
#define ERR_PROGRAM_LOG_MALLOC   4 // Allocate memory for a shader program's linking log failed
#define ERR_SHADER_OBJECT_MALLOC 5 // Allocating memory for a new ShaderProgram object failed


// Assert that a value holds, printing an error message and exiting if not.
#define assertion(asdf_assertion) assertFun(asdf_assertion, __FILE__, __FUNCTION__, __LINE__)

// Ignore this function. Use the macro instead.
void assertFun(bool assertion, char *p_file, const char *p_function, int line_number);