#include <glad/glad.h>
#include <stdio.h>
#include "shader_program.h"
#include "../assertion/assertion.h"




// Helper functions
GLuint compile_shader(GLint shader_type, const char *p_source);
GLuint create_program(const char *p_vertex_shader, const char *p_fragment_shader);




// Shader Source
static const GLchar* VERTEX_SHADER_SOURCE =
   "#version 150                        \n"
   "                                    \n"
   "in vec4 position;                   \n"
   "                                    \n"
   "void main() {                       \n"
   "   const vec2 quad[4] = vec2[4](    \n"
   "      vec2(0.0, 0.0),               \n"
   "      vec2(0.5, 0.0),               \n"
   "      vec2(0.5, 0.5),               \n"
   "      vec2(0.0, 0.5)                \n"
   "   );                               \n"
   "                                    \n"
   "   gl_Position = vec4(quad[gl_VertexID], 0.0, 1.0); \n"
   "}                                   \n"
   ;


static const GLchar* FRAGMENT_SHADER_SOURCE =
   "#version 150                                \n"
   "                                            \n"
   "uniform sampler2D texture;                  \n"
   "                                            \n"
   "void main() {                               \n"
   "   gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0); \n"
   "}                                           \n"
   ;




struct ShaderProgram {
   GLuint program_id; // GPU Provided id of The Program's compiled and linked program
};


void ShaderProgram_new(ShaderProgram **p_p_shader_program) {
   assertion(p_p_shader_program != NULL, "Tried to initialize a new Program on a NULL pointer.");
   assertion(*p_p_shader_program != NULL, "Tried to initialize a new Program on a NULL pointer.");

   // Allocate memory for new program
   ShaderProgram *p_shader_program = malloc(sizeof(ShaderProgram));
   assertion(p_shader_program != NULL, "Unable to allocate memory for The Program's structure.");

   // Initialize program
   p_shader_program->program_id = create_program(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);

   // "Return" new program to caller
   *p_p_shader_program = p_shader_program;
}


void ShaderProgram_drop(ShaderProgram **p_p_shader_program) {
   assertion(p_p_shader_program != NULL, "Tried to drop a Program on a NULL pointer.");
   assertion(*p_p_shader_program != NULL, "Tried to drop a Program on a NULL pointer.");
   printf("\nDropping program.");

   // Clean up program resources
   ShaderProgram *p_shader_program = *p_p_shader_program;
   glDeleteProgram(p_shader_program->program_id);
   free(p_shader_program);

   // Set caller's pointer to NULL
   *p_p_shader_program = NULL;
}


void ShaderProgram_draw(ShaderProgram *p_shader_program) {
   glUseProgram(p_shader_program->program_id);
   glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
   glUseProgram(0);
}


GLuint compile_shader(GLint shader_type, const char *p_source) {
   // Create the shader
   GLuint shader_id = glCreateShader(shader_type);
   glShaderSource(shader_id, 1, &p_source, NULL);
   glCompileShader(shader_id);

   // Ensure the shader compiled successfully
   GLint compile_status;
   glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);

   if (compile_status != GL_TRUE) {
      GLint log_length;
      glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

      char *p_log_buffer = malloc(log_length * sizeof(char));
      assertion(p_log_buffer != NULL, "Unable to allocate memory for the shader compile error log.");
      glGetShaderInfoLog(shader_id, log_length, NULL, p_log_buffer);

      printf("\nUnable to compile the shader.");
      printf("\nReason: %s", p_log_buffer);

      free(p_log_buffer);

      glDeleteShader(shader_id);

      exit(-1);
   }

   return shader_id;
}


GLuint create_program(const char *p_vertex_shader, const char *p_fragment_shader) {
   // Create the shaders
   GLuint vertex_shader_id = compile_shader(GL_VERTEX_SHADER, p_vertex_shader);
   GLuint fragment_shader_id = compile_shader(GL_FRAGMENT_SHADER, p_fragment_shader);

   // Create the program
   GLuint program_id = glCreateProgram();
   glAttachShader(program_id, vertex_shader_id);
   glAttachShader(program_id, fragment_shader_id);
   glLinkProgram(program_id);

   // Cleanup the shaders
   glDeleteShader(vertex_shader_id);
   glDeleteShader(fragment_shader_id);

   // Ensure the program was created successfully
   GLint program_status;
   glGetProgramiv(program_id, GL_LINK_STATUS, &program_status);

   if (program_status != GL_TRUE) {
      GLint log_length;
      glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);

      char *p_log_buffer = malloc(log_length * sizeof(char));
      assertion(p_log_buffer != NULL, "Unable to allocate memory for shader error log.");
      glGetProgramInfoLog(program_id, log_length, NULL, p_log_buffer);

      printf("\nUnable to link the shader program.");
      printf("\nReason: %s", p_log_buffer);

      free(p_log_buffer);

      glDeleteProgram(program_id);

      exit(-1);
   }

   return program_id;
}