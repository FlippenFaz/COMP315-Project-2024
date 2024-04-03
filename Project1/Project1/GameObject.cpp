/*
  Edited by Avesh Ramavather (created),...

  [Add name above after editing]
*/

#include <iostream>
#include <vector>

// Include necessary header files
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Bullet.h"

std::vector<Bullet*> bullets;

int timeLastBullet = 0;

// Constructor definition
GameObject::GameObject(const char* textureSheet, SDL_Renderer* renderer, int x, int y, int type)
{
	this->renderer = renderer;
    this->type = type;

    // Load texture using TextureManager
    objTexture = TextureManager::LoadTexture(textureSheet, renderer);

    // Adjust properties based on type (Check GameObject.h for types)
    
    // If the game object is an overlay (type == 2)
    if (type == 2) {
        changeOpacity();
    }

    if (type == 0)
    {   
        // Initial xpos = -50 and ypos = 128 compensates for the character sprite used, we can make it better
        xpos = -50;
        ypos = 128;

        srcRect.h = 64;
        srcRect.w = 128;
        srcRect.y = 0;

        
        destRect.h = srcRect.h * 1.5;
        destRect.w = srcRect.w * 1.5;
    }
    // For backgrounds and overlays (type != 0) for now, we will add more stuff here
    else
    {
        
        xpos = x;
        ypos = y;

        srcRect.h = 600;
        srcRect.w = 800;
        srcRect.x = 0;
        srcRect.y = 0;

        destRect.x = xpos;
        destRect.y = ypos;
        destRect.h = srcRect.h;
        destRect.w = srcRect.w;
    }
    
}

// Destructor definition
GameObject::~GameObject() 
{

}


// Update function definition
void GameObject::update()
{
    // Get the state of the keyboard
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    
    // Passes keyboard input to the move function
    this->move(currentKeyStates);
}

// Handles player movement
void GameObject::move(const Uint8* currentKeyStates)
{
    // Handle keyboard inputs
    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        xpos += 5;
    }
    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        xpos -= 5;
    }
    if (currentKeyStates[SDL_SCANCODE_UP])
    {
        ypos -= 5;
    }
    if (currentKeyStates[SDL_SCANCODE_DOWN])
    {
        ypos += 5;
    }

    
    // Change texture based on keyboard input, used for implementing animations
    // Note: currentKeyStates[SDL_SCANCODE_RIGHT] == 0 is checking if the right arrow key is NOT being pressed
    if (currentKeyStates[SDL_SCANCODE_RIGHT] == 0 && currentKeyStates[SDL_SCANCODE_LEFT] == 0 && currentKeyStates[SDL_SCANCODE_UP] == 0 && currentKeyStates[SDL_SCANCODE_DOWN] == 0)
    {
        // Idle animation
        SDL_DestroyTexture(objTexture);
        this->objTexture = TextureManager::LoadTexture("assets/idlet.png", renderer);
        srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / 100) % 8);

        if (currentKeyStates[SDL_SCANCODE_SPACE] != 0)
        {
            // Shoot animation - change 5 below to increase/decrease animation speed
            SDL_DestroyTexture(objTexture);
            this->objTexture = TextureManager::LoadTexture("assets/shot_1t.png", renderer);
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / 5) % 4);
            
            
            // Create a bullet
            if (SDL_GetTicks() > (timeLastBullet + 200))
            {
                timeLastBullet = SDL_GetTicks();
                Bullet* bulletptr = new Bullet();
                bulletptr->createBullet(this->renderer, this->xpos, this->ypos);
                bullets.push_back(bulletptr);
            }
        }
    }
    else
    {
        // Run animation
        SDL_DestroyTexture(objTexture);
        this->objTexture = TextureManager::LoadTexture("assets/runt.png", renderer);
        srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / 100) % 8);
    }

    // Update the position of the character
    destRect.x = xpos;
    destRect.y = ypos;

    // Update the bullets position
    for (std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end();) {
        if (it == bullets.end()) {
            break;
        }
        Bullet* bulletPtr = *it;
        bulletPtr->update();
        // If the bullet has exceeded its range - DESTROY IT!
        if (bulletPtr->checkActiveBullet() == false)
        {
            it = bullets.erase(it);
            //it = bullets.begin();
            //it--;
            delete bulletPtr;
            bulletPtr = nullptr;
        } else {
            it++;
        }
    }
}
// Render function definition
void GameObject::render()
{
    // Render the object
	SDL_RenderCopy(this->renderer, objTexture, &srcRect, &destRect);
    for (Bullet* bullet : bullets)
    {
        bullet->render();
    }
}

// Function to change opacity
void GameObject::changeOpacity()
{
    SDL_SetTextureBlendMode(objTexture, SDL_BLENDMODE_BLEND);

    // Set the opacity of the overlay (0 = fully transparent, 255 = fully opaque)
    SDL_SetTextureAlphaMod(objTexture, 125);
}