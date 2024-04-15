/*
 
  Edited by Avesh Ramavather (created),...
  Jaedon Naidu
  Faran Steenkamp
  [Add name above after editing]

*/

#pragma once

// Include necessary header files
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"

using namespace std;

class Login: public level
{
public:
	// Constructor
	Login(/*Game* g*/);

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

	void setActive(bool b);

	//@jaedonnaidu: added to check if username already exists;
	bool usernameExists(string s);

	string nameSuggestor(string userInput);

	//@Daniel Hogg: added methods to work with level class

	void setBackground();

	void setPlayerInvolved();


private:

	//@author: Faran
	//Needs to be friend to be able to access login.renderer
	friend int EventWatchForTyping(void* userdata, SDL_Event* event);

	// Indicates if the login screen is still active
	//Game* ga;

	bool checkActive = false;

	// Texture for the login screen
	SDL_Texture* objTexture;

	// Source and destination for rendering
	SDL_Rect srcRect, destRect;

	// Renderer for rendering the login screen
	//SDL_Renderer* renderer;
};
