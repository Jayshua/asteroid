#pragma once

// Represents a texture that can be drawn to the screen
struct Texture;
typedef struct Texture Texture;

// Allocate and initialize a new texture using the image at the provided path
void Texture_new(Texture **p_p_texture, char *p_file_path);

// Free resources and pointer allocation for the given texture
void Texture_drop(Texture **p_p_texture);