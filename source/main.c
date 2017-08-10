#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "assertion/assertion.h"
#include "texture/texture.h"
#include "shader_program/shader_program.h"



GLFWwindow *create_window() {
   if (!glfwInit()) {
      printf("Unable to initialize GLFW. Exiting program.");
      exit(-1);
   }

   GLFWwindow *p_window = glfwCreateWindow(640, 480, "Astroids", NULL, NULL);
   assertion(p_window != NULL);

   glfwMakeContextCurrent(p_window);

   return p_window;
}


int main() {
   GLFWwindow *p_window = create_window();
   assertion(gladLoadGL());

   // Create the shader program
   ShaderProgram *p_shader_program;
   ErrorCode shader_program_result = ShaderProgram_new(&p_shader_program);
   if (shader_program_result != SUCCESS) {
      printf("Failed to create shader program. Abort is now inevitable. Resistance is futile.");
      printf("\nError code %d", shader_program_result);
      glfwTerminate();
      exit(-1);
   }

   // Create the sprite texture
   Texture *p_texture;
   Texture_new(&p_texture, "assets/ship.png");

   while (!glfwWindowShouldClose(p_window)) {
      glClearColor(1.0, 0.0, 0.0, 1.0);
      glClear(GL_COLOR_BUFFER_BIT);

      ShaderProgram_draw(p_shader_program);

      glfwSwapBuffers(p_window);
      glfwPollEvents();
   }

   Texture_drop(&p_texture);
   ShaderProgram_drop(&p_shader_program);
   glfwTerminate();

   return 0;
}