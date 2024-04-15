/*
 
  Edited by Avesh Ramavather (created),...
  Jaedon Naidu
  Neo Kekana
  [Add name above after editing]

*/

// Include necessary header files
#include "Login.h"
#include "SDL.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "RenderText.h"
#include "Game.h"
#include "GameObject.h"

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
RenderText* suggestionText; //Archan

// User input
string userInput = "";
string warningInput = "";
string suggestionInput = ""; //Archan

// Event
SDL_Event event;
bool exitflag;

// Constructor
Login::Login(/*Game* g*/) {
	//this->ga = g;
	/*srcRect.h = 720;
	srcRect.w = 1280;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = 0;
	destRect.y = 0;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;*/
	// Create RenderText object for username display
	usernameText = new RenderText(80, 335, 50, renderer, "Spy name:  ", { 0 ,0 ,0 }, 300);
	userInputText = new RenderText(515, 300, 110, renderer, userInput.c_str(), { 0, 0, 0 }, 0);
	warningText = new RenderText(620, 460, 50, renderer, warningInput.c_str(), { 255, 0, 0 }, 400);
	//  x  y  FONTsize  Colour   TextWidth
	suggestionText = new RenderText(620, 560, 50, renderer, suggestionInput.c_str(), { 255, 0, 0 }, 400);

	SDL_StartTextInput();

	setPlayerInvolved();
}

// / Method used to create the login screen
//not necessary
/*void Login::createLoginScreen(const char* textureSheet, SDL_Renderer* renderer)
{
	// Store renderer for the login screen
	//this->renderer = renderer;
	//exitflag = false;
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
	//checkActive = true;

	// Create RenderText object for username display
	usernameText = new RenderText(80, 335, 50, renderer, "Spy name:  ", {0 ,0 ,0}, 300);
	userInputText = new RenderText(515, 300, 110, renderer, userInput.c_str(), {0, 0, 0}, 0);
	warningText = new RenderText(620, 460, 50, renderer, warningInput.c_str(), {255, 0, 0}, 400);
	//  x  y  FONTsize  Colour   TextWidth
	suggestionText = new RenderText(620, 560, 50, renderer, suggestionInput.c_str(), {255, 0, 0}, 400);

	SDL_StartTextInput();
	
}*/

// Method used to update the login screen
void Login::update()
{
	// Get the state of the keyboard
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);


	//change level flag here?@Daniel Hogg
	if ((currentKeyStates[SDL_SCANCODE_L] != 0) && ((currentKeyStates[SDL_SCANCODE_LCTRL] != 0) || (currentKeyStates[SDL_SCANCODE_RCTRL] != 0)))
	{
		//g->setGameState("leaderboard");
		//this->setActive(false);
		
		//@Daniel Hogg: tells the if statement in the game class to go into itself and changes the flag to level 1
		//tells update function in game class to update the level to leaderboard
		level::tracker->setFlagChanged(true);
		//sets the level flag to the next level's level flag
		tracker->setLevelFlag(1);

	}

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
	
	//Edited: @Archan: added the Name suggestion text message
	if (userInput.length() == 10)
	{
		warningInput = "10 CHARS MAX";
		warningText->updateText(this->renderer, warningInput);

		if (usernameExists(userInput)) {
			suggestionInput = "Suggestion: " + nameSuggestor(userInput);
			suggestionText->updateText(this->renderer, suggestionInput);
		}
			
	}else
	{
		warningInput = "";
		warningText->updateText(this->renderer, warningInput);
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
	//Edit: @Archan: added a name suggestor method which uniquely creates usernames
	if (displayWarning) { //if theres a warning any input key clears it EXCEPT backspace(this isn't wokring as intended)
		warningInput.erase(0, warningInput.length());
		warningText->updateText(this->renderer, warningInput);
			
		displayWarning = false; // reset
	}
	

	// Press enter to continue to game if the username enetered is of the appropriate length
	//Edited: @Archan: added a simple method to suggest avialable usernames
	if (userInput.length() >= 3 && userInput.length() <= 10) {
		if (usernameExists(userInput))
		{
			warningInput = "Taken";
			warningText->updateText(this->renderer, warningInput);
			
			//Archan: adding name suggestions
			suggestionInput = "Suggestion: " + nameSuggestor(userInput);
			suggestionText->updateText(this->renderer, suggestionInput); 

		}
		else if ((warningInput != "TAKEN") && (warningInput != "TOO SHORT") && currentKeyStates[SDL_SCANCODE_RETURN] != 0)
		{
			//@jaedonnaidu: Welcome user
			string welcomeMessage = "Welcome, " + userInput + "...";
			SDL_ShowSimpleMessageBox(NULL, "Spy accepted", welcomeMessage.c_str(), NULL);
			


			// Used to open/create a text file in overwrite mode. Use ios::app to append.
			ofstream file("textfiles/PlayerInfo.txt", ios::trunc);

			// Adds username to a player info textfile found at "textfiles/PlayerInfo.txt"
			string outputString = userInput + "\n";
			file << outputString;

			file.close();

			// Sets the login screens active status to false
			//this->g->setGameState("level 1");
			//Login::checkActive = false;

			//@Daniel Hogg: tells the if statement in the game class to go into itself and changes the flag to level 1
		    //tells update function in game class to update the level
			level::tracker->setFlagChanged(true);
			//sets the level flag to the next level's level flag
			tracker->setLevelFlag(2);
		}
	}
	// Sets and renders the warning display to "TOO SHORT"
	else if (userInput.length() > 0 && userInput.length() < 3)
	{
		warningInput = "TOO SHORT";
		displayWarning = true;
		warningText->updateText(this->renderer, warningInput);

		//clearing Suggestion text : @Archan
		suggestionInput = " ";
		suggestionText->updateText(this->renderer, suggestionInput);
	}
	else
	{
		warningInput = "START TYPING...";
		displayWarning = true;
		warningText->updateText(this->renderer, warningInput);
	}

}

//Edited: @Archan: Added this method for name suggestions
string Login::nameSuggestor(string userInput) {
	//Creates a name for the user incase they're struggling to create one
	string username = userInput;
	string suggestedName = "";
	bool isLastCharDigit = false; 
	char temp = ' ';

	if (username.length() >= 3 && username.length() <= 7) { //adding on a number to the name
		suggestedName = username + "007";
		if (!usernameExists(suggestedName)) { //suggestedName is unique
			username = suggestedName;
			return username;
		}
	}

	if(username.length() == 10) { //max chars
		if (!isdigit(username[username.length() - 1])) {  //last char isn't a Number
			
			username.pop_back(); //removes last char		
		}
		else { // last char is a number
			temp = username[username.length()-1]; // keeping last digit 
			//cout << temp;
			isLastCharDigit = true;
			username.pop_back();
			username.pop_back();

		}
		
	}
	//appending name with numbers
	for (int i = 1; i <= 9; i++) {
		username += to_string(i); 
		
		if (isLastCharDigit) {
			username += temp; //returning the original digit this had at the end
		}
		if (!usernameExists(username)) { //username is unique
			isLastCharDigit = false;
			return username;
		}
		else {
			username.pop_back();
			username.pop_back();
		}
	}

	return "";

}

//edit: @jaedonnaidu: just checks if username already exists on system
//edit: @aveshramavather: fixed bug where it returned true for any sub string of the player name
//						  and now searches sub string from beginning of each line until the first delimiter "$"

/* New leaderboard text file format:
*				name$level 1 score$level 2 score$level 3 score$level 4 score$total score$(optional? total time)
* 
*/

//we'll maintain this leaderboard constantly sorted by total score. That way outputting to leaderboard is easy and it
//maintains the look of a 'leaderboard'. So when we insert a player's name, we have to do the work of figuring out where it goes.

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
	//SDL_RenderCopy(this->renderer, objTexture, &srcRect, &destRect);

	// Render the login screen text
	usernameText->RenderTextOnScreen(this->renderer);

	userInputText->RenderTextOnScreen(this->renderer);

	warningText->RenderTextOnScreen(this->renderer);

	suggestionText->RenderTextOnScreen(this->renderer);
}

// Method to check if login screen is active
bool Login::isActive()
{
	return checkActive;
}

//Method to set login to be active or not
void Login::setActive(bool b)
{
	checkActive = b;
}

//@Daniel Hogg: added method implementations to work with level class

void Login::setBackground() {

	back->setObjTexture("assets/loginBackground.png");

}

// Destructor
Login::~Login()
{
	delete usernameText;
	delete userInputText;
	delete warningText;
}

void Login::setPlayerInvolved() {
	this->playerInvolvmentStatus = false;
}