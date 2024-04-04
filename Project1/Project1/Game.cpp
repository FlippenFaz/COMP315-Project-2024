/*
  Edited by Avesh Ramavather (created),...

  [Add name above after editing]
*/

#include <iostream>

// Include necessary header files
#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Login.h"
#include "SDL_ttf.h"

GameObject* player;
GameObject* back;
GameObject* overlay;

SDL_Event Game::event;

Login* login;

// Constructor
Game::Game()
{

}

// Destructor
Game::~Game()
{

}

// Initialization function definition
void Game::initialize(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{	
	// Used to assign a window to fullscreen (Maybe an additional feature where we allow the user to change between windowed and fullscreen?)
	int flags = 0;
	if (fullscreen == true) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// Initializing SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem initialized" << std::endl;

		// Creating a window and testing if it was created successfully
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		// Creating a renderer and testing if it was created successfully
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;

	}
	else
	{
		isRunning = false;
	}

	// Creating login screen
	login = new Login();
	login->createLoginScreen("assets/login.png", renderer);
	

	// Creating game objects: 
	
	// Background 
	back = new GameObject("assets/Gridlines.png", renderer, 0, 0, 1);

	// Player
	player = new GameObject("assets/idlet.png", renderer, 0, 0, 0);


	// DO NOT REMOVE - REQUIRED FOR THE NIGHT VISION LEVEL
	//overlay = new GameObject("assets/night_vision/GRN.bmp", renderer, 0, 0, 2);
	
}

// Event handling function definition
void Game::handleEvents()
{
	
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

// Update function definition
void Game::update()
{
	if (login != NULL && login->isActive())
	{
		login->update();
	}
	else
	{
		player->update();
	}
	
}

// Render function definition
void Game::render()
{
	SDL_RenderClear(renderer);
	
	if (login != NULL && login->isActive())
	{
		login->render();
	}
	else
	{
		back->render();
		player->render();
		// NIGHT VISION
		//overlay->render();
	}
	
	SDL_RenderPresent(renderer);
}

// Clean function definition
void Game::clean() 
{
	// Destroying window, renderer, and quitting SDL
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game Cleaned" << std::endl;
}

