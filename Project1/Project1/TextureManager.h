/*
  Edited by Avesh Ramavather (created),...

  [Add name above after editing]
*/

#pragma once

// Include necessary header files
#include "Game.h"

// Declaration of TextureManager class
class TextureManager
{
public:
	// Function to load a texture from file
	static SDL_Texture* LoadTexture(const char* filename, SDL_Renderer* renderer);
};
