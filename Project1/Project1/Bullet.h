/*
  Created by Avesh Ramavather

  Edited by Avesh Ramavather (created), Jaedon Naidu, Daniel Hogg(added simple getters), 
  
  [Add name above after editing]
*/
#pragma once

#include "SDL.h"

class Bullet
{
public:
	// Constructor
	Bullet();
	// Destructor
	~Bullet();

	// Function to create a bullet
	void createBullet(SDL_Renderer* renderer, int xpos, int ypos, bool flip);

	// Function to update bullet position
	void update();

	// Function to render bullet
	void render();

	// Function to check if bullet is active
	bool checkActiveBullet();

	//getters for level classes
	int getXPos();

	int getYPos();

private:
	// Member variables
	int xpos;
	int ypos;
	bool flip;

	bool checkActive;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};
