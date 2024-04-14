/*

  Edited by Jaedon Naidu (created),...
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
#include "Leaderboard.h"

#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <windows.h>

using namespace std;

// Rendering text
RenderText* leaderboardUsernameText[10];
RenderText* scoreText[10];

// User input
string userName = "";


// Event
//SDL_Event event;
bool Leaderboardexitflag;

// Constructor
Leaderboard::Leaderboard(Game* g) {
	this->g = g;
}

// / Method used to create the login screen
void Leaderboard::createLeaderboardScreen(const char* textureSheet, SDL_Renderer* renderer)
{
	// Store renderer for the login screen
	this->renderer = renderer;
	Leaderboardexitflag = false;
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

	// Edit @NeoKekana
	// Setting the leaderboard screen to false because the escape key wasn't responding, but I called update in the game class so that
	// the input can be registered
	// Set leaderboard screen as active
	checkActive = false;

	// Create RenderText objects. We'll need 10 for each of username and score, since we want all of these to be on screen at the same time
	for (int i = 0; i < 10; i++)
	{
		leaderboardUsernameText[i] = new RenderText(175, 100 + i * 59, 50, renderer, "TestScore", { 0 ,0 ,0 }, 300);
		scoreText[i] = new RenderText(565, 100 + i * 59, 50, renderer, "TestScore", { 0 ,0 ,0 }, 300);
	}
	

}

//method to get total score given the username, using the leaderboard textfile
int Leaderboard::getTotalUserScore(string username)
{
	ifstream file("textfiles/Leaderboard.txt");
	string line;
	string buffer;
	int pos;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			pos = line.find('$');
			buffer = line.substr(0, pos);
			line.erase(0, pos + 1);
			if (buffer == username)
			{
				for (int i = 0; i < 4; i++)
				{
					pos = line.find('$');
					buffer = line.substr(0, pos);
					line.erase(0, pos + 1);
				}
				return stoi(line);
			}
		}

	}
}

//method to go through the leaderboard textfiles and display all the usernames and total scores
void Leaderboard::displayUsernames()
{
	ifstream file("textfiles/Leaderboard.txt");
	string line;
	string username;
	int pos;
	int score;
	int counter = 0;
	int lineGapPixels = 1;
	if (file.is_open())
	{
		while (getline(file, line))
		{
			pos = line.find('$');
			username = line.substr(0, pos);
			line.erase(0, pos + 1);
			score = getTotalUserScore(username);
			leaderboardUsernameText[counter]->updateText(this->renderer, username);
			scoreText[counter]->updateText(this->renderer, to_string(score));
			counter++;
		}

	}
}

// Method used to update the leaderboard screen
void Leaderboard::update()
{
	// Get the state of the keyboard
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	displayUsernames();

	if (currentKeyStates[SDL_SCANCODE_ESCAPE] != 0)
	{
		checkActive = false;
		this->g->setGameState("login");

	}

}

// Method to render the leaderboard screen
void Leaderboard::render()
{
	// Render the leaderboard screen texture
	SDL_RenderCopy(this->renderer, objTexture, &srcRect, &destRect);

	// Render the leaderboard screen text
	for(int i=0; i<10; i++)
	{
		leaderboardUsernameText[i]->RenderTextOnScreen(this->renderer);
		scoreText[i]->RenderTextOnScreen(this->renderer);
	}
	
}

// Method to check if leaderboard screen is active
bool Leaderboard::isActive()
{
	return checkActive;
}

void Leaderboard::setActive(bool b)
{
	checkActive = b;
}

// Destructor
Leaderboard::~Leaderboard()
{
	delete[] leaderboardUsernameText;
	delete[] scoreText;
}