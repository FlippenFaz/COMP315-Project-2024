/*
  Edited by Avesh Ramavather (created),...
  Jaedon Naidu
  [Add name above after editing]
*/

// Include necessary header files
#include "SDL.h"
#include "Game.h"
#include <iostream>
#include <thread>
#include <windows.h>

using namespace std;

std::string workingdir();
void playVideo();
void killVideo();

int main(int argc, char* args[])
{
	//comment this out for coding so you don't have to watch this video play
	playVideo();
	this_thread::sleep_for(chrono::milliseconds(93000)); //replace this with the length of the video we end up using
	killVideo();
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
	TCHAR szPath[] = TEXT("assets\\IntroVideoCompressed.mp4"); //replace this with the actual video

	HINSTANCE hRet = ShellExecute(
		HWND_DESKTOP, //Parent window
		TEXT("open"),       //Operation to perform
		szPath,       //Path to program
		NULL,         //Parameters
		NULL,         //Default directory
		SW_SHOW);     //How to open


	//system("TASKKILL /F /IM wmplayer.exe");

	//if video could not be found
	if ((LONG)hRet <= 32)
	{
		std::cout << "cannot find file";
		std::cout << "Current working directory: " << workingdir();
	}
}

//@Faran
//Method to kill most common video players
void killVideo() {
	system("TASKKILL /F /IM Microsoft.Media.Player.exe");
	system("TASKKILL /F /IM wmplayer.exe");
	system("TASKKILL /F /IM vlc.exe");
}

//@jaedonnaidu
//debugging function in case the video is not found; it would help to see the directory we are currently in
std::string workingdir()
{
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}