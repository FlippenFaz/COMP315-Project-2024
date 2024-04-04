/*
 
  Edited by Avesh Ramavather (created),...

  [Add name above after editing]

*/

#pragma once

// Include necessary header files
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <string>

class RenderText
{
public:
	// Constructor
	RenderText(int xpos, int ypos, int fontSize, SDL_Renderer* renderer, std::string text, SDL_Color color);

	// Destructor
	~RenderText();

	// Method to render text on screen
	void RenderTextOnScreen(SDL_Renderer* renderer);

	// Update text dynamically
	void updateText(SDL_Renderer* renderer, std::string text);

private:
	// Size of the font
	int fontSize;

	// Text for rendering
	std::string text;

	// Color of text
	SDL_Color color;

	// Font used for rendered text
	TTF_Font* font;

	// Texture for the rendered text
	SDL_Texture* objTexture;

	// Destination for text
	SDL_Rect destRect;

	// Renderer for rendering text
	SDL_Renderer* renderer;
};