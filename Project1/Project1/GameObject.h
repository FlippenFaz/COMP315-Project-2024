/*
  Edited by Avesh Ramavather (created),...
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