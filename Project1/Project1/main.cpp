/*
  Edited by Avesh Ramavather (created),...

  [Add name above after editing]
*/

//This is a test edit

// Include necessary header files
#include "SDL.h"
#include "Game.h"


int main(int argc, char* args[])
{
	// Number of frames per second
	const int FPS = 60;
	// Amount of time each frame should take
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	// Creating an instance of the game
	Game* game;
	game = new Game();

	game->initialize("Test Run", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	// Keeps the game running until an intervention occurs
	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		// Adds delay to keep the time between frames consistent
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	// Destroys certain graphics components that were created like the window, renderer, etc.
	game->clean();

	// Frees up the memory that was allocated for the game
	delete game;
	return 0;
}