/*
  Created by Avesh Ramavather

  //Edited by Avesh Ramavather (created), Jaedon Naidu, Daniel Hogg(added simple getters), 
  
  [Add name above after editing]
*/

// Include necessary header files
#include "Bullet.h"
#include "TextureManager.h"
#include <iostream>
#include "GameObject.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::createBullet(SDL_Renderer* renderer, int xpos, int ypos, bool flip)
{

	// Load texture for bullet
	objTexture = TextureManager::LoadTexture("assets/Bullets/1.png", renderer);
	
	this->renderer = renderer;
	this->xpos = xpos;
	this->ypos = ypos;
	this->flip = flip;

	// Define source and destination rectangles for rendering
	srcRect.h = 10;
	srcRect.w = 10;
	srcRect.x = 0;
	srcRect.y = 0;

	// If facing left bullet should spawn in a separate place
	if(flip)
	{
		destRect.x = xpos + 50;
	}else
	{
		destRect.x = xpos + 128;
	}
	destRect.y = ypos + 20;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;

	// Set bullet to active
	checkActive = true;
}

void Bullet::update() 
{
	// Move bullet
	if(flip)
	{
		destRect.x -= 10;
	}else
	{
		destRect.x += 10;
	}
	

	// Check if bullet is out of bounds
	if (destRect.x >= 900 || destRect.x <= -80)
	{
		checkActive = false;
	}
}

void Bullet::render()
{
	// Render bullet
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

bool Bullet::checkActiveBullet()
{
	// Return status of the bullet
	return checkActive;
}

int Bullet::getXPos() {
	return this->destRect.x;
}

int Bullet::getYPos() {
	return this->destRect.y;
}