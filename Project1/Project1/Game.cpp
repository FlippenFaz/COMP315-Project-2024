/*
  Edited by Avesh Ramavather (created),...
  Jaedon Naidu (login events)
  Neo Kekana (debugger)
  [Add name above after editing]
*/

#include <iostream>

// Include necessary header files
#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Login.h"
#include "SDL_ttf.h"
#include "Leaderboard.h"
#include "Question.h"
#include "RenderText.h"

GameObject* player;
GameObject* back;
GameObject* overlay;

SDL_Event Game::event;

Login* login;
Leaderboard* leaderboard;

RenderText* question;

// Constructor
Game::Game()
{
	gameState = "";
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
	login = new Login(this);
	login->createLoginScreen("assets/loginBackground.png", renderer);

	//Creating a leaderboard
	leaderboard = new Leaderboard(this);
	leaderboard->createLeaderboardScreen("assets/leaderboard.png", renderer);
	leaderboard->update();
	
	// Creating game objects:
	
	// Background 
	back = new GameObject("assets/Gridlines.png", renderer, 0, 0, 1);
	// Player
	player = new GameObject("assets/idlet.png", renderer, 0, 0, 0);

	// @Neo the vector for the level 1 questions is initialized.
	vector<Question> questions = readQuestionsFromFile("textfiles/level1QuestionBank.txt");
	
	/*question = new RenderText(0, 0, 50, renderer, questions[0].toString(), { 0 ,0 ,0 }, 300);*/

	// gameState = "";
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
		delete(login); 
		login = NULL;
		break;

	//@jaedonnaidu
	//code to make sure the top right cross works even with login screen
	case SDL_WINDOWEVENT:
		if(event.window.event == SDL_WINDOWEVENT_CLOSE)
		{
			isRunning = false;
			delete(login);
			login = NULL;
			break;
		}
	default:
		break;
	}
}

// Update function definition
void Game::update()
{
	
	//modified by @jaedonnaidu to work with the gameState variable
	//leaderboard can currently be accessed with CTRL + L, from the login page
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if(gameState == "level 1")
	{
		player->update();
		// Edit @NeoKekana
		// Allow the user to check the leaderboard in game (need to have it as a pause function)
		/*if ((currentKeyStates[SDL_SCANCODE_L] != 0) && ((currentKeyStates[SDL_SCANCODE_LCTRL] != 0) || (currentKeyStates[SDL_SCANCODE_RCTRL] != 0)))
		{
			setGameState("leaderboard");
			leaderboard->setActive(true);

		}*/

		if (currentKeyStates[SDL_SCANCODE_ESCAPE] != 0)
		{
			string quitMessage = "GO BACK TO LOGIN SCREEN?";
			const SDL_MessageBoxButtonData buttons[] = {
				{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "OK" },
				{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Cancel" }
			};
			const SDL_MessageBoxData messageboxdata = {
				SDL_MESSAGEBOX_INFORMATION,
				NULL,
				"Quit?",
				quitMessage.c_str(),
				SDL_arraysize(buttons),
				buttons,
				NULL
			};
			int result = SDL_ShowMessageBox(&messageboxdata, &result);
			if (result == 1) {
				setGameState("login");
				login->setActive(true);
				render();
			}


		}
	}
	else if (login != NULL && login->isActive() || (gameState == "login"))
	{
		login->setActive(true);
		login->update();
	}

	else if ((leaderboard != NULL && leaderboard->isActive()) || (gameState == "leaderboard"))
	{
		leaderboard->setActive(true);
		leaderboard->update();
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
	else if (leaderboard != NULL && leaderboard->isActive())
	{

		leaderboard->render();

	}else
	{
		back->render();
		player->render();



		// NIGHT VISION
		//overlay->render();
	}
	
	SDL_RenderPresent(renderer);


	/*VALUES OF GAMESTATE USED SO FAR:
	login
	leaderboard
	level 1*/
}
void Game::setGameState(string str)
{
	gameState = str;
}

// Edit @NeoKekana
// A getter for the game state
string Game::getGameState()
{
	return gameState;
}

SDL_Window* Game::getWindow()
{
	return window;
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

// @Neo Kekana 
// function for reading question from the text file and creating question objects for each question. Each question object needs a render
vector<Question> Game::readQuestionsFromFile(const string& filename) {
	vector<Question> questions;

	ifstream file(filename); // Open the file for reading
	if (!file.is_open()) {
		cerr << "Error: Could not open file " << filename << endl;
		return questions;
	}

	string line;
	while (getline(file, line)) {
		// Skip lines that don't start with the 1 or 0
		if (line[0] != '0' || line[0] != '1')
			continue;
		// Create Question object from the line
		Question q(line);
		questions.push_back(q);
	}

	file.close(); // Close the file
	return questions;
}
