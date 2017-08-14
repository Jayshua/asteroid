GLFWwindow *create_window() {
   if (!glfwInit()) {
      printf("Unable to initialize GLFW. Exiting program.");
      exit(-1);
   }

   GLFWwindow *p_window = glfwCreateWindow(640, 480, "Astroids", NULL, NULL);

   glfwMakeContextCurrent(p_window);

   return p_window;
}
