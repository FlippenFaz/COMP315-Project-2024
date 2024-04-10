/*
  Edited by Avesh Ramavather (created),Daniel(added level transition and tracking/swapping implementation)

  [Add name above after editing]
*/

// Header file for the Game class
#pragma once

// Include necessary header files
#include "SDL.h"
#include "SDL_image.h"
#include "levelTracker.h"
#include "level.h"

class Game
{
public:
	Game();
	~Game();

	// Initialize the game window
	void initialize(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	// Handle events
	void handleEvents();

	// Update the game state
	void update();

	// Render the game graphics
	void render();

	// Clean up resources before exiting
	void clean();

	// Check if the game is running
	bool running() 
	{ 
		return isRunning; 
	}

	// Static event instance for handling events
	static SDL_Event event;

private:

	// Indicating whether the game is running
	bool isRunning;

	// SDL window instance
	SDL_Window* window;

	// SDL renderer instance for rendering graphics
	SDL_Renderer* renderer;

	levelTracker* lvlTracker;
	level* currentLevel;

};
