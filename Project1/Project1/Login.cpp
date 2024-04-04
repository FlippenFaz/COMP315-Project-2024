/*
 
  Edited by Avesh Ramavather (created),...
  Jaedon Naidu
  [Add name above after editing]

*/

// Include necessary header files
#include "Login.h"
#include "SDL.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "RenderText.h"

#include <iostream>
#include <string>
#include <fstream>
#include <thread>

using namespace std;

// Rendering text
RenderText* usernameText;
RenderText* userInputText;

// User input
string userInput = "";

// Event
SDL_Event event;

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
	usernameText = new RenderText(100, 300, 110, renderer, "Username:  ", {0 ,0 ,0});
	userInputText = new RenderText(600, 300, 110, renderer, userInput.c_str(), {0, 0, 0});

	SDL_StartTextInput();
	
}

// Method used to update the login screen
void Login::update()
{
	// Get the state of the keyboard
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	
	// Ensures that the user can enter at most 10 characters for their name
	if (userInput.length() < 10) 
	{
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_TEXTINPUT:
				// Checking if a character is being inputted
				if (event.text.text[0] != '\0') {
					userInput += event.text.text;
					userInputText->updateText(this->renderer, userInput);
				}
				break;
			}
		}
	}
	
	// If the user presses backspace, it clears their entire entry
	//Edit: @jaedonnaidu: it's now able to backspace one character at a time
	if (currentKeyStates[SDL_SCANCODE_BACKSPACE] != 0)
	{
		//don't allow to backspace if string is empty
		if(userInput.length() > 0)
		{
			//erase a character
			userInput.erase(userInput.length() - 1, 1);

			//update the text
			userInputText->updateText(this->renderer, userInput);

			//use a small wait because a standard backspace key press takes around 200ms, so we wouldn't want one press to continue deleting characters
			this_thread::sleep_for(chrono::milliseconds(200));
		}
		
	}

	// Press enter to continue to game if the username enetered is of the appropriate length
	if (currentKeyStates[SDL_SCANCODE_RETURN] != 0
		&& userInput.length() >= 3
		&& userInput.length() <= 10)
	{

		if(usernameExists(userInput))
		{
			userInput = "TAKEN";
			userInputText->updateText(this->renderer, userInput);
			this_thread::sleep_for(chrono::milliseconds(200));
		}else if(userInput != "TAKEN")
		{
			// Used to open/create a text file in overwrite mode, use "std::ios::app" in the last parameter to append a text file
			ofstream file("textfiles/LoginInfo.txt", ios::app);

			// Adds username to a user login info textfile found at "textfiles/LoginInfo.txt"
			string outputString = userInput + "\n";
			file << outputString;

			file.close();

			// Sets the login screen to false;
			Login::checkActive = false;
		}
		
	}

	
}

//edit: @jaedonnaidu: just checks if username already exists on system
bool Login::usernameExists(string s){
	ifstream file("textfiles/LoginInfo.txt");
	string line;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			if (line == s)
			{
				return true;
			}
		}
		return false;
	}
}

// Method to render the login screen
void Login::render()
{
	// Render the login screen texture
	SDL_RenderCopy(this->renderer, objTexture, &srcRect, &destRect);

	// Render the login screen text
	usernameText->RenderTextOnScreen(this->renderer);

	userInputText->RenderTextOnScreen(this->renderer);
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
	delete userInputText;
}