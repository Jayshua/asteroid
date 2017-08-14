void create_texture(GLuint *p_texture_id) {
   // Create the OpenGL Texture
   GLuint texture_id;
   glGenTextures(1, &texture_id);
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, texture_id);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // Get the image
   int width, height, bit_depth;
   unsigned char *p_image = stbi_load("assets/sprite.png", &width, &height, &bit_depth, 4);
   if (p_image == NULL) {
      printf("\nUnable to load texture. Ending now.");
      exit(-1);
   }

   // Upload the image to the GPU
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, p_image);

   // Cleanup the image data
   stbi_image_free(p_image);

   // Return the OpenGL image
   *p_texture_id = texture_id;
}
