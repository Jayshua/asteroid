#pragma once
#include "../assertion/assertion.h"

// Represents the shader program on the GPU used to draw the game
// The game only has a single shader - so I decided to call it simply "The Program"
// Has a nice ring to it, don't you think?
struct ShaderProgram;
typedef struct ShaderProgram ShaderProgram;

// Allocate and initialize The Program.
ErrorCode ShaderProgram_new(ShaderProgram **p_shader_program) MUST_USE_RETURN;

// Free any resources associated with The Program (include The Program's pointer itself)
void ShaderProgram_drop(ShaderProgram **p_shader_program);

// Use The Program to draw to the screen
void ShaderProgram_draw(ShaderProgram *p_shader_program);
