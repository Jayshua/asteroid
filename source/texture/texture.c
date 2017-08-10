#include <glad/glad.h>
#include <stb_image.h>
#include "../assertion/assertion.h"
#include "texture.h"



struct Texture {
   GLuint texture_id;
};



void Texture_new(Texture **p_p_texture, char *p_file_path) {
   assertion(p_p_texture != NULL);

   // Initialize the new texture
   Texture *p_texture = malloc(sizeof(Texture));
   glGenTextures(1, &(p_texture->texture_id));
   glBindTexture(GL_TEXTURE_2D, p_texture->texture_id);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glBindTexture(GL_TEXTURE_2D, 0);

   // Get the image and load it into the texture
   int width, height, bit_depth;
   unsigned char *p_image = stbi_load(p_file_path, &width, &height, &bit_depth, 4);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, p_image);
   stbi_image_free(p_image);

   // "Return" the new texture to the caller
   *p_p_texture = p_texture;
}




void Texture_drop(Texture **p_p_texture) {
   assertion(p_p_texture != NULL);
   assertion(*p_p_texture != NULL);

   // Clean up resources used by the texture
   Texture *p_texture = *p_p_texture;
   glDeleteTextures(1, &(p_texture->texture_id));
   free(p_texture);

   // Set the callers pointer to NULL since it no longer points to valid memory
   *p_p_texture = NULL;
}