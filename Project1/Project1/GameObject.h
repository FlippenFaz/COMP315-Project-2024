/*
  Edited by Avesh Ramavather (created), Daniel Hogg(added getters and setters for level classes access), 
  [Add name above after editing]
*/

#pragma once

// Include necessary header files
#include "Game.h"
#include "Bullet.h"

class GameObject
{

public:

	//Constructor
	GameObject(const char* textureSheet, SDL_Renderer* ren, int x, int y, int type);

	// Destructor
	~GameObject();

	// Update function used to continuously update the state of a game object
	void update();

	// Move function to move the character
	void move(const Uint8* currentKeyStates);

	// render function 
	void render();

	// Change opacity function - mainly used to set the tone for a night vision level
	void changeOpacity();

	//potential fix to back problem
	void setObjTexture(const char* path);

	//setter methods to set x and y positions for the level's classes to use
	void setXPos(int XPos);

	void setYPos(int YPos);

	//setter and getter methods to get info about the bullets for level classes to determin if a question was answered
	bool getBulletDestroyed();

	int getBulletXPos();

	int getBulletYPos();

	void setBulletDestroyed();

private:

	//Member variables
	int xpos;
	int ypos;

	/* Defined a member variable called type.
	*  This allows us to have multiple game objects falling under the same class.
	*  Different types are handled/are given different properties in the implementation of an instance of a game object (check GameObject.cpp).
	* 
	*  The current types are:
	* 
	*  0 - represents playable character
	*  1 - represents a background
	*  2 - represents an overlay on the screen (night vision)
	* 
	*  If new types are created, please list them here.
	*/
	int type;
	

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};