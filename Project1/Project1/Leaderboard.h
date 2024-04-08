/*

  Edited by Jaedon Naidu (created),...
  [Add name above after editing]

*/

#pragma once

// Include necessary header files
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"

using namespace std;

class Leaderboard
{
public:
	// Constructor
	Leaderboard(Game* g);

	// Destructor
	~Leaderboard();

	// Method used to create the leaderboard screen
	void createLeaderboardScreen(const char* textureSheet, SDL_Renderer* renderer);

	// Update method for leaderboard screen
	void update();

	// Render method for leaderboard screen
	void render();

	// Method used to check if the leaderboard screen is still active
	bool isActive();

	void setActive(bool b);

	//Method to display usernames from textfile
	void displayUsernames();

	int getTotalUserScore(string username);

private:
	// Indicates if the leaderboard screen is still active
	Game* g;

	bool checkActive = false;

	// Texture for the leaderboard screen
	SDL_Texture* objTexture;

	// Source and destination for rendering
	SDL_Rect srcRect, destRect;

	// Renderer for rendering the leaderboard screen
	SDL_Renderer* renderer;
};
