/*
  Edited by Avesh Ramavather (created),...

  [Add name above after editing]
*/

// Include necessary header files
#include "TextureManager.h"

// Definition of the LoadTexture function
SDL_Texture* TextureManager::LoadTexture(const char* texture, SDL_Renderer* renderer)
{
	// Load image surface
	SDL_Surface* tempSurface = IMG_Load(texture);

	// Create texture from surface
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);

	// Free loaded surface
	SDL_FreeSurface(tempSurface);

	return tex;
}