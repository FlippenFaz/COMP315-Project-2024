/*
  Edited by Avesh Ramavather (created),...
  Jaedon Naidu
  Faran Steenkamp
  [Add name above after editing]
*/

// Include necessary header files
#include "SDL.h"
#include "Game.h"
#include <iostream>
#include <thread>
#include <windows.h>
#include <process.h>

using namespace std;


std::string workingdir();
void playVideo();
void killVideo(HWND handle);
bool videoPlaying;

int main(int argc, char* args[])
{
	//comment this out for coding so you don't have to watch this video play
	videoPlaying = true;
	playVideo();
	while(videoPlaying)
	{
		
	}
	// 
	// Number of frames per second
	const int FPS = 60;
	// Amount of time each frame should take
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	// Creating an instance of the game
	Game* game;
	game = new Game();
	game->setGameState("login");
	game->initialize("Test Run", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);//make it true for the real thing to hide video player once done playing

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

//@jaedonnaidu
//method to play a video
void playVideo() {
	TCHAR szPath[] = TEXT("assets\\Welcome, human.mp4"); //replace this with the actual video

	HINSTANCE hRet = ShellExecute(
		HWND_DESKTOP, //Parent window
		TEXT("open"),       //Operation to perform
		szPath,       //Path to program
		NULL,         //Parameters
		NULL,         //Default directory
		SW_SHOW);     //How to open
	auto start = std::chrono::high_resolution_clock::now();

	//get coordinates to centralize video
	int horizontal = GetSystemMetrics(SM_CXSCREEN);
	int vertical = GetSystemMetrics(SM_CYSCREEN);

	//a handle is an abstraction of the actual resource it points to
	HWND handle;
	handle = ::FindWindow(NULL, TEXT("Media Player"));
	SetWindowPos(handle, 0, (horizontal-1280)/2, (vertical-720)/2, 1280,720, NULL );

	if (!handle)
	{
		handle = ::FindWindow(NULL, TEXT("Windows Media Player"));
		SetWindowPos(handle, 0, (horizontal - 1280) / 2, (vertical - 720) / 2, 1280, 720, NULL);
	}

	if (!handle)
	{
		handle = ::FindWindow(NULL, TEXT("Windows Media Player Legacy"));
		SetWindowPos(handle, 0, (horizontal - 1280) / 2, (vertical - 720) / 2, 1280, 720, NULL);
	}

	if (!handle)
	{
		handle = ::FindWindow(NULL, TEXT("Windows Media Player Legacy"));
		SetWindowPos(handle, 0, (horizontal - 1280) / 2, (vertical - 720) / 2, 1280, 720, NULL);
	}

	//if video could not be found
	if ((LONG)hRet <= 32)
	{
		std::cout << "cannot find file";
		std::cout << "Current working directory: " << workingdir();
	}

	

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	
	while((elapsed.count() < 3) && videoPlaying)
	{
		end = std::chrono::high_resolution_clock::now();
		elapsed = end - start;
		videoPlaying = true;
		
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_SPACE] != 0)
		{
			videoPlaying = false;
		}
		
	}


	killVideo(handle);
}

//@Faran
//Method to kill most common video players
//Modified: @jaedonnaidu: taskkill wasn't working so this is a more direct way
void killVideo(HWND handle) {
	PostMessage(handle, WM_CLOSE, 0, 0);
	videoPlaying = false;
}

//@jaedonnaidu
//debugging function in case the video is not found; it would help to see the directory we are currently in
std::string workingdir()
{
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}