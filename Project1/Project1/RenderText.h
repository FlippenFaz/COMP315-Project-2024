/*
 
  Edited by Avesh Ramavather (created),...
  [Add name above after editing]

*/

#pragma once

// Include necessary header files
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class RenderText
{
public:
	// Constructor
	RenderText(int xpos, int ypos, int fontSize, SDL_Renderer* renderer, const char* text, SDL_Color color);

	// Destructor
	~RenderText();

	// Method to render text on screen
	void RenderTextOnScreen(SDL_Renderer* renderer);

private:
	// Font used for rendered text
	TTF_Font* font;

	// Texture for the rendered text
	SDL_Texture* objTexture;

	// Destination for text
	SDL_Rect destRect;

	// Renderer for rendering text
	SDL_Renderer* renderer;
};