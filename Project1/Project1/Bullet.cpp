/*
  Created by Avesh Ramavather

  Edited by Avesh Ramavather (created),...

  [Add name above after editing]
*/

// Include necessary header files
#include "Bullet.h"
#include "TextureManager.h"
#include <iostream>

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::createBullet(SDL_Renderer* renderer, int xpos, int ypos)
{
	// Load texture for bullet
	objTexture = TextureManager::LoadTexture("assets/Bullets/1.png", renderer);

	this->renderer = renderer;
	this->xpos = xpos;
	this->ypos = ypos;

	// Define source and destination rectangles for rendering
	srcRect.h = 10;
	srcRect.w = 10;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos + 128;
	destRect.y = ypos + 20;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;

	// Set bullet to active
	checkActive = true;
}

void Bullet::update() 
{
	// Move bullet
	destRect.x += 5;

	// Check if bullet is out of bounds
	if (destRect.x >= 550)
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