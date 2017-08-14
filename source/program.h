static const GLchar* VERTEX_SHADER =
   "#version 420                                                \n"
   "                                                            \n"
   "layout (location = 0) in vec2 vertex_position;              \n"
   "layout (location = 2) in vec2 texture_position;             \n"
   "                                                            \n"
   "uniform vec2 viewport;                                      \n"
   "uniform vec2 texture_offset;                                \n"
   "uniform vec3 position; // (x, y, rotation)                  \n"
   "                                                            \n"
   "out vec2 fs_texture_position;                               \n"
   "                                                            \n"
   "void main() {                                               \n"
   "   fs_texture_position = texture_position + texture_offset; \n"
   "                                                            \n"
   "   vec2 screen_position = vec2(                             \n"
   "      (vertex_position.x + position.x) / viewport.x,        \n"
   "      (vertex_position.y + position.y) / viewport.y         \n"
   "   );                                                       \n"
   "                                                            \n"
   "   gl_Position = vec4(screen_position, 0.0, 1.0);           \n"
   "}                                                           \n"
   ;


static const GLchar* FRAGMENT_SHADER =
   "#version 420                                             \n"
   "                                                         \n"
   "in vec2 fs_texture_position;                             \n"
   "                                                         \n"
   "uniform sampler2D texture1;                              \n"
   "                                                         \n"
   "void main() {                                            \n"
   "  gl_FragColor = texture(texture1, fs_texture_position); \n"
   // "  if (color.w < 0.001) {                                 \n"
   // "     gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);            \n"
   // "  } else {                                               \n"
   // "     gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);            \n"
   // "  }                                                      \n"
   "}                                                        \n"
   ;


void create_shader(GLuint *p_shader_id, GLint shader_type, const char *p_source) {
   GLuint shader_id = glCreateShader(shader_type);
   glShaderSource(shader_id, 1, &p_source, NULL);
   glCompileShader(shader_id);

   GLint compile_status;
   glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);

   if (compile_status != GL_TRUE) {
      GLint log_length;
      glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

      char *p_log_buffer = malloc(log_length * sizeof(char));
      glGetShaderInfoLog(shader_id, log_length, NULL, p_log_buffer);

      printf("\nUnable to create the shader. %d", log_length);
      printf("\nLog: %s", p_log_buffer);

      free(p_log_buffer);
      glDeleteShader(shader_id);

      exit(-1);
   }

   *p_shader_id = shader_id;
}



void create_program(GLuint *p_program_id, const char *p_vertex_shader, const char *p_fragment_shader) {
   // Create the shaders
   GLuint vertex_shader_id;
   create_shader(&vertex_shader_id, GL_VERTEX_SHADER, p_vertex_shader);

   GLuint fragment_shader_id;
   create_shader(&fragment_shader_id, GL_FRAGMENT_SHADER, p_fragment_shader);

   // Create the program
   GLuint program_id = glCreateProgram();
   glAttachShader(program_id, vertex_shader_id);
   glAttachShader(program_id, fragment_shader_id);
   glLinkProgram(program_id);

   // Cleanup the shaders
   glDeleteShader(vertex_shader_id);
   glDeleteShader(fragment_shader_id);

   // Check if the program was created successfully
   GLint program_status;
   glGetProgramiv(program_id, GL_LINK_STATUS, &program_status);

   if (program_status != GL_TRUE) {
      GLint log_length;
      glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);

      char *p_log_buffer = malloc(log_length * sizeof(char));
      glGetProgramInfoLog(program_id, log_length, NULL, p_log_buffer);

      printf("\nUnable to create the program. %d", log_length);
      printf("\nLog: %s", p_log_buffer);

      free(p_log_buffer);
      glDeleteProgram(program_id);

      exit(-1);
   }

   *p_program_id = program_id;
}
