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
#include "Game.h"

#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <windows.h>

using namespace std;

// Rendering text
RenderText* usernameText;
RenderText* userInputText;
RenderText* warningText;

// User input
string userInput = "";
string warningInput = "";

// Event
SDL_Event event;
bool exitflag;

// Constructor
Login::Login(Game* g){
	this->g = g;
}

// / Method used to create the login screen
void Login::createLoginScreen(const char* textureSheet, SDL_Renderer* renderer)
{
	// Store renderer for the login screen
	this->renderer = renderer;
	exitflag = false;
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
	usernameText = new RenderText(100, 300, 110, renderer, "Spy name:  ", {0 ,0 ,0});
	userInputText = new RenderText(600, 300, 110, renderer, userInput.c_str(), {0, 0, 0});
	warningText = new RenderText(110, 420, 50, renderer, warningInput.c_str(), {255, 0, 0});

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
	//Edited: @Archan: added else statement, clears Warning with any key press, this is incase a user forgets to 
	//					use Backspace, previously the warning would be included as part of the username
	//                  ISSUE: doing this broke backspace clearing the warning, it still works to go back a character though
	//Edit: @aveshramavather: Fixed the warning display bug and cleaned up the implementation
	bool displayWarning = (warningInput == "TOO SHORT" || warningInput == "TAKEN");
	if (currentKeyStates[SDL_SCANCODE_BACKSPACE] != 0)
	{
		//don't allow to backspace if string is empty
		if (userInput.length() > 0)
		{
			// Removes one character from the player name
			userInput.erase(userInput.length() - 1, 1);

			//update the text
			userInputText->updateText(this->renderer, userInput);

			//use a small wait because a standard backspace key press takes around 200ms, so we wouldn't want one press to continue deleting characters
			this_thread::sleep_for(chrono::milliseconds(200));
		}

	}

	//@Archan: Comment out this else statement to revert back to Original Code
	//Edit: @aveshramavather: Fixed warning display
	if (displayWarning) { //if theres a warning any input key clears it EXCEPT backspace(this isn't wokring as intended)
			
		warningInput.erase(0, warningInput.length());
		warningText->updateText(this->renderer, warningInput);
			
		displayWarning = false; // reset
	}
	

	// Press enter to continue to game if the username enetered is of the appropriate length
	if (userInput.length() >= 3 && userInput.length() <= 10) {
		if (usernameExists(userInput))
		{
			warningInput = "TAKEN";
			warningText->updateText(this->renderer, warningInput);
		}
		else if ((warningInput != "TAKEN") && (warningInput != "TOO SHORT") && currentKeyStates[SDL_SCANCODE_RETURN] != 0)
		{
			// Used to open/create a text file in overwrite mode. Use ios::app to append.
			ofstream file("textfiles/PlayerInfo.txt", ios::trunc);

			// Adds username to a player info textfile found at "textfiles/PlayerInfo.txt"
			string outputString = userInput + "\n";
			file << outputString;

			file.close();

			// Sets the login screens active status to false
			Login::checkActive = false;
		}
	}
	// Sets and renders the warning display to "TOO SHORT"
	else if (userInput.length() > 0 && userInput.length() < 3)
	{
		warningInput = "TOO SHORT";
		displayWarning = true;
		warningText->updateText(this->renderer, warningInput);
	}
	else
	{
		warningInput = "START TYPING...";
		displayWarning = true;
		warningText->updateText(this->renderer, warningInput);
	}

}

//edit: @jaedonnaidu: just checks if username already exists on system
//edit: @aveshramavather: fixed bug where it returned true for any sub string of the player name
//						  and now searches sub string from beginning of each line until the first delimiter "$"

/* New leaderboard text file format:
*				name$level 1 score$level 2 score$level 3 score$level 4 score$total score$(optional? total time)
* 
*/
bool Login::usernameExists(string s){
	ifstream file("textfiles/Leaderboard.txt");
	string line;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			int pos = line.find('$');
			
			if (pos != -1 && line.substr(0, pos) == s)
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

	warningText->RenderTextOnScreen(this->renderer);
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
	delete warningText;
	g->clean();
}