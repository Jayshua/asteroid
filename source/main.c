#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "program.h"
#include "window.h"
#include "vertex_buffer.h"
#include "texture.h"


typedef struct {
   float x;
   float y;
} Point;

Point Point_add(Point left, Point right) {
   return (Point){
      .x = left.x + right.x,
      .y = left.y + right.y
   };
}

Point Point_mul(Point left, float scalar) {
   return (Point) {
      .x = left.x * scalar,
      .y = left.y * scalar
   };
}


typedef struct {
   bool up, down, left, right;
} Controls;

Controls Controls_new(GLFWwindow *p_window) {
   return (Controls) {
      .up    = glfwGetKey(p_window, GLFW_KEY_UP),
      .down  = glfwGetKey(p_window, GLFW_KEY_DOWN),
      .left  = glfwGetKey(p_window, GLFW_KEY_LEFT),
      .right = glfwGetKey(p_window, GLFW_KEY_RIGHT)
   };
}


typedef struct {
   Point location;
   Point velocity;
} Hero;

Hero Hero_new() {
   return (Hero) {
      .location = (Point) {.x = 0.0, .y = 0.0},
      .velocity = (Point) {.x = 0.0, .y = 0.0}
   };
}

void Hero_print(Hero *p_hero) {
   printf("\nHero: {Location: %f, %f; Velocity: %f, %f}",
      p_hero->location.x,
      p_hero->location.y,
      p_hero->velocity.x, 
      p_hero->velocity.y);
}

void Hero_step(Hero *p_hero, Controls controls) {
   if (controls.up) {
      p_hero->velocity.y += 0.1;
   }

   if (controls.down) {
      p_hero->velocity.y -= 0.1;
   }

   if (controls.left) {
      p_hero->velocity.x -= 0.1;
   }

   if (controls.right) {
      p_hero->velocity.x += 0.1;
   }

   p_hero->velocity = Point_mul(p_hero->velocity, 0.9);
   p_hero->location = Point_add(p_hero->location, p_hero->velocity);
}


// typedef unsigned short WORD;

// typedef struct {
//   WORD wYear;
//   WORD wMonth;
//   WORD wDayOfWeek;
//   WORD wDay;
//   WORD wHour;
//   WORD wMinute;
//   WORD wSecond;
//   WORD wMilliseconds;
// } SYSTEMTIME;

// void GetSystemTime(SYSTEMTIME lpSystemTime);


typedef struct {
   float last_tick_time;
   float physics_overflow;
} GameClock;


// This function will fail at hour turnover. That should probably be fixed at some point.
void GameClock_tick(GameClock *p_clock) {
   // The SYSTEMTIME struct and GetSystemTime function are defined in windows.h which is included by GLFW
   SYSTEMTIME time;
   GetSystemTime(&time);
   float current_time = time.wMinute + ((float)time.wSecond / 60.0) + ((float)time.wMilliseconds / 60000.0);
   float difference = current_time - p_clock->last_tick_time;
   p_clock->physics_overflow += difference;
   p_clock->last_tick_time = current_time;
}

GameClock GameClock_new() {
   GameClock game_clock = {0};
   GameClock_tick(&game_clock);
   game_clock.physics_overflow = 0;
   return game_clock;
}


void GameClock_print(GameClock *p_clock) {
   printf("\nGameClock: {last_tick_time: %f, physics_overflow: %f}", p_clock->last_tick_time, p_clock->physics_overflow);
}



int main() {
   // Create the window
   GLFWwindow *p_window = create_window();

   // Setup OpenGL
   if (!gladLoadGL()) {
      printf("\nUnable to initialize OpenGL. The program must now abort. Resistance is futile.");
      exit(-1);
   }

   // Create the shader program
   GLuint program_id;
   create_program(&program_id, VERTEX_SHADER, FRAGMENT_SHADER);

   // Create the vertex array
   GLuint vertex_array_id;
   GLuint vertex_buffer_id;
   create_vertex_buffer(&vertex_array_id, &vertex_buffer_id);

   // Create the texture sprite
   GLuint texture_id;
   create_texture(&texture_id);

   // Enable alpha transparency in textures
   // glEnable(GL_BLEND);
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   // Create the game objects
   GameClock game_clock = GameClock_new();
   // Hero my_hero = Hero_new();


   // Loop until the user exits
   while (!glfwWindowShouldClose(p_window)) {
      GameClock_tick(&game_clock);

      // while (game_clock.physics_overflow > 1.0) {
      //    game_clock.physics_overflow -= 1.0;
      //    Hero_step(Controls_new(p_window));
      // }

      // Clear the screen
      glClearColor(1.0, 0.0, 0.0, 1.0);
      glClear(GL_COLOR_BUFFER_BIT);

      // Draw the scene
      glUseProgram(program_id);
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, texture_id);
      glBindVertexArray(vertex_array_id);
      int width, height;
      glfwGetWindowSize(p_window, &width, &height);
      glUniform2f(glGetUniformLocation(program_id, "viewport"), (float)width, (float)height);
      glUniform2f(glGetUniformLocation(program_id, "texture_offset"), 0.12, 0.33);
      glUniform3f(glGetUniformLocation(program_id, "position"), 0.1, 0.0, 0.0);
      glDrawArrays(GL_TRIANGLES, 0, 6);

      // Swap the back and front buffers
      glfwSwapBuffers(p_window);

      // Handle incoming events
      glfwPollEvents();
   }


   // Cleanup the program
   glDeleteProgram(program_id);
   glDeleteBuffers(1, &vertex_buffer_id);
   glDeleteVertexArrays(1, &vertex_array_id);
   glDeleteTextures(1, &texture_id);
   glfwTerminate();


   return 0;
}