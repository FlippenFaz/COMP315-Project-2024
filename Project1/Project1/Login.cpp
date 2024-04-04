/*
 
  Edited by Avesh Ramavather (created),...
  [Add name above after editing]

*/

// Include necessary header files
#include "Login.h"
#include "SDL.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "RenderText.h"

#include <iostream>

// Rendering text
RenderText* usernameText;

// Constructor
Login::Login(){

}

// / Method used to create the login screen
void Login::createLoginScreen(const char* textureSheet, SDL_Renderer* renderer)
{
	// Store renderer for the login screen
	this->renderer = renderer;

	// Load login screen texture
	objTexture = TextureManager::LoadTexture(textureSheet, renderer);

	srcRect.h = 720;
	srcRect.w = 1280;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = 0;
	destRect.y = 0;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;

	// Set login screen as active
	checkActive = true;

	// Create RenderText object for username display
	usernameText = new RenderText(100, 300, 100, renderer, "Username:  ", {0,0,0});
}

// Method used to update th login screen
void Login::update()
{
	// Get the state of the keyboard
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	
	// Press enter to continue to game
	if (currentKeyStates[SDL_SCANCODE_RETURN] != 0)
	{
		Login::checkActive = false;
	}
}

// Method to render the login screen
void Login::render()
{
	// Render the login screen texture
	SDL_RenderCopy(this->renderer, objTexture, &srcRect, &destRect);

	// Render the username text
	usernameText->RenderTextOnScreen(this->renderer);
}

// Method to check if login screen is active
bool Login::isActive()
{
	return checkActive;
}

// Destructor
Login::~Login()
{
	delete usernameText;
}