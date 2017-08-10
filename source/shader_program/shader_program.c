#include <glad/glad.h>
#include <stdio.h>
#include "shader_program.h"
#include "../assertion/assertion.h"




// Helper functions
ErrorCode compile_shader(GLuint *p_shader_id, GLint shader_type, const char *p_source) MUST_USE_RETURN;
ErrorCode create_program(GLuint *p_program_id, const char *p_vertex_shader, const char *p_fragment_shader) MUST_USE_RETURN;




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


ErrorCode ShaderProgram_new(ShaderProgram **p_p_shader_program) {
   assertion(p_p_shader_program != NULL);
   assertion(*p_p_shader_program != NULL);

   // Allocate memory for new program
   ShaderProgram *p_shader_program = malloc(sizeof(ShaderProgram));
   if (p_shader_program == NULL)
      return ERR_SHADER_OBJECT_MALLOC;

   // Initialize program
   ErrorCode program_result = create_program(&(p_shader_program->program_id), VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);
   if (program_result != SUCCESS)
      return program_result;

   // "Return" new program to caller
   *p_p_shader_program = p_shader_program;

   return SUCCESS;
}


void ShaderProgram_drop(ShaderProgram **p_p_shader_program) {
   assertion(p_p_shader_program != NULL);
   assertion(*p_p_shader_program != NULL);
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







ErrorCode compile_shader(GLuint *p_shader_id, GLint shader_type, const char *p_source) {
   assertion(p_shader_id != NULL);

   // Create the shader
   GLuint shader_id = glCreateShader(shader_type);
   glShaderSource(shader_id, 1, &p_source, NULL);
   glCompileShader(shader_id);

   // Ensure the shader compiled successfully
   GLint compile_status;
   glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);

   if (compile_status != GL_TRUE) {
      // Allocate memory for the error log messages
      GLint log_length;
      glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
      char *p_log_buffer = malloc(log_length * sizeof(char));
      if (p_log_buffer == NULL)
         return ERR_SHADER_LOG_MALLOC;

      // Get the error log
      glGetShaderInfoLog(shader_id, log_length, NULL, p_log_buffer);

      // Print the error log
      printf("\nUnable to compile the shader.");
      printf("\nReason: %s", p_log_buffer);

      // Cleanup
      free(p_log_buffer);
      glDeleteShader(shader_id);

      return ERR_SHADER_COMPILE;
   }

   *p_shader_id = shader_id;

   return SUCCESS;
}


ErrorCode create_program(GLuint *p_program_id, const char *p_vertex_shader, const char *p_fragment_shader) {
   assertion(p_program_id != NULL);

   // Create the vertex shader
   GLuint vertex_shader_id;
   ErrorCode vertex_shader_result = compile_shader(&vertex_shader_id, GL_VERTEX_SHADER, p_vertex_shader);
   if (vertex_shader_result != SUCCESS)
      return vertex_shader_result;

   // Create the fragment shader
   GLuint fragment_shader_id;
   ErrorCode fragment_shader_result = compile_shader(&fragment_shader_id, GL_FRAGMENT_SHADER, p_fragment_shader);
   if (fragment_shader_result != SUCCESS)
      return fragment_shader_result;

   // Create the program
   GLuint program_id = glCreateProgram();
   glAttachShader(program_id, vertex_shader_id);
   glAttachShader(program_id, fragment_shader_id);
   glLinkProgram(program_id);

   // Cleanup the the shaders
   glDeleteShader(vertex_shader_id);
   glDeleteShader(fragment_shader_id);

   // Ensure the program was created successfully
   GLint program_status;
   glGetProgramiv(program_id, GL_LINK_STATUS, &program_status);

   if (program_status != GL_TRUE) {
      // Allocate memory for the error log
      GLint log_length;
      glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);
      char *p_log_buffer = malloc(log_length * sizeof(char));
      if (p_log_buffer == NULL)
         return ERR_PROGRAM_LOG_MALLOC;

      // Get the compile log
      glGetProgramInfoLog(program_id, log_length, NULL, p_log_buffer);

      // Print the compile log
      printf("\nUnable to link the shader program.");
      printf("\nReason: %s", p_log_buffer);

      // Cleanup
      free(p_log_buffer);
      glDeleteProgram(program_id);

      return ERR_PROGRAM_LINK;
   }

   *p_program_id = program_id;

   return SUCCESS;
}