/*
 
  Edited by Avesh Ramavather (created),...
  [Add name above after editing]

*/

#pragma once

// Include necessary header files
#include "SDL.h"
#include "SDL_image.h"

class Login
{
public:
	// Constructor
	Login();

	// Destructor
	~Login();

	// Method used to create the login screen
	void createLoginScreen(const char* textureSheet, SDL_Renderer* renderer);

	// Update method for login screen
	void update();

	// Render method for login screen
	void render();

	// Method used to check if the login screen is still active
	bool isActive();

private:
	// Indicates if the login screen is still active
	bool checkActive = false;

	// Texture for the login screen
	SDL_Texture* objTexture;

	// Source and destination for rendering
	SDL_Rect srcRect, destRect;

	// Renderer for rendering the login screen
	SDL_Renderer* renderer;
};
