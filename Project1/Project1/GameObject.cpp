/*
  Edited by Avesh Ramavather (created), Jaedon Naidu, Daniel Hogg(added getters and setters),

  [Add name above after editing]
  
*/

#include <iostream>

// Include necessary header files
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Bullet.h"

Bullet* bullet = nullptr;

//used to possibly flip the player sprite
bool flip;
bool reachedBottom;
bool reachedTop;
bool reachedLeft;
bool reachedRight;

//for level classes(Daniel Hogg)
bool bulletDestroyed;
int bulletLastXPos;
int bulletLastYPos;

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
        ypos = 149;

        srcRect.h = 64;
        srcRect.w = 128;
        srcRect.y = 0;

        
        destRect.h = srcRect.h * 1.8;
        destRect.w = srcRect.w * 1.8;
    }
    // For backgrounds and overlays (type != 0) for now, we will add more stuff here
    else
    {
        
        xpos = x;
        ypos = y;

        srcRect.h = 720;
        srcRect.w = 1280;
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
    // Only if the character isn't on the boundary of what's in-bounds
    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        if (xpos <= 700)
        {
            flip = false;
            reachedLeft = false;
            xpos += 5;
        }
        else
        {
            reachedRight = true;
        }

    }
    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        if (xpos >= -50)
        {
            flip = true;
            reachedRight = false;
            xpos -= 5;
        }
        else
        {
            reachedLeft = true;
        }
    }
    if (currentKeyStates[SDL_SCANCODE_UP])
    {
        if (ypos >= 150)
        {
            reachedBottom = false;
            ypos -= 5;
        }
        else
        {
            reachedTop = true;
        }
    }
    if (currentKeyStates[SDL_SCANCODE_DOWN])
    {
        if (ypos <= 590)
        {
            reachedTop = false;
            ypos += 5;
        }
        else
        {
            reachedBottom = true;
        }
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

            //if the bullet hasn't been shot yet then the space should trigger the shooting animation
            if (bullet == nullptr)
            {
                this->objTexture = TextureManager::LoadTexture("assets/shot_1t.png", renderer);

                //otherwise we won't allow the user to shoot so the shot animation should not fire
                // Issue above is that the shoot animation does not complete before going back to idle state (Avesh)
            }
            else
            {
                this->objTexture = TextureManager::LoadTexture("assets/idlet.png", renderer);
            }


            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / 5) % 4);

            // Create a bullet
            if (bullet == nullptr)
            {
                bullet = new Bullet();
                bullet->createBullet(this->renderer, this->xpos, this->ypos, flip);
            }
        }
    }
    else
    {
        // Run animation

        if ((currentKeyStates[SDL_SCANCODE_RIGHT] != 0 && (!reachedRight))
            || (currentKeyStates[SDL_SCANCODE_LEFT] != 0 && (!reachedLeft))
            || (currentKeyStates[SDL_SCANCODE_UP] != 0 && (!reachedTop))
            || (currentKeyStates[SDL_SCANCODE_DOWN] != 0 && (!reachedBottom)))
        {
            SDL_DestroyTexture(objTexture);
            this->objTexture = TextureManager::LoadTexture("assets/runt.png", renderer);
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / 100) % 8);
        }else
        {
            this->objTexture = TextureManager::LoadTexture("assets/idlet.png", renderer);
        }
    }

    // Update the position of the character
    destRect.x = xpos;
    destRect.y = ypos;

    // Update the bullets position
    if (bullet != nullptr) {
        bullet->update();
        // If the bullet has exceeded its range - DESTROY IT!
        if (bullet->checkActiveBullet() == false)
        {
            bulletLastXPos = bullet->getXPos();
            bulletLastYPos = bullet->getYPos();
            delete bullet;
            bullet = nullptr;
            //used to determin if a question has been answered(Daniel Hogg)
            bulletDestroyed = true;
        }
    }
}
// Render function definition
void GameObject::render()
{
    // Render the object 
	
    //we can flip the man to run left if necessary
    if(flip && type == 0)
    {
        SDL_RenderCopyEx(this->renderer, objTexture, &srcRect, &destRect, 0, 0, SDL_FLIP_HORIZONTAL);
    }else
    {
        SDL_RenderCopy(this->renderer, objTexture, &srcRect, &destRect);
    }

    if (bullet != nullptr)
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

//simple getters and setters for the level classes
void GameObject::setXPos(int XPos) {
    xpos = XPos;
}

void GameObject::setYPos(int YPos) {
    ypos = YPos;
}

bool GameObject::getBulletDestroyed(){
    return bulletDestroyed;
}

int GameObject::getBulletXPos() {
    return bulletLastXPos;
}

int GameObject::getBulletYPos() {
    return bulletLastYPos;
}

void GameObject::setBulletDestroyed() {

    bulletDestroyed = false;
}

void GameObject::setObjTexture(const char* path) {
    this->objTexture = TextureManager::LoadTexture(path, renderer);
}