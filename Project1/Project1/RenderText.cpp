/*
 
  Edited by Avesh Ramavather (created),...

  [Add name above after editing]

*/

// Include necessary header files
#include "RenderText.h"

#include <iostream>

/* Constructor
   parameters:  xpos: The x coordinate of where you need the text to start from (left)
				ypos: The y coordinate of where you need the text to start from (top)
				fontSize: The size of the font you require
				renderer: A pointer to the main renderer
                text: The actual words that you need to be displayed
                color: The color of the text in which color = {255, 255, 255} is white and {0, 0, 0} is black following {R, G, B} colors
                       eg. You can pass in "{255, 255, 255}" without quotes to get the text color to be white
*/ //int xpos, int ypos, int fontSize, SDL_Renderer* renderer, std::string text, SDL_Color color
RenderText::RenderText(int xpos, int ypos, int fontSize, SDL_Renderer* renderer, std::string text, SDL_Color color)
{
    // Initialize SDL_ttf
    TTF_Init();

    // Store the renderer
    this->renderer = renderer;

    // Load the font
    font = TTF_OpenFont("fonts/DeterminationMono.ttf", fontSize);

    // Render text onto surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

    // Create texture from surface
    objTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    // Store the renderer
    this->renderer = renderer;

    // Store the text color
    this->color = color;

    // Store the font size
    this->fontSize = fontSize;

    // Set the destination of the rendered text
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = std::string(text).length()*fontSize/2;
    destRect.h = fontSize;
}

// Destructor
RenderText::~RenderText()
{
    // Free resources
    TTF_CloseFont(font);
    SDL_DestroyTexture(objTexture);

    // Quit TTF_Quit
    TTF_Quit();
}

// Method to render text on screen
void RenderText::RenderTextOnScreen(SDL_Renderer* renderer)
{
    // Render text on screen
    SDL_RenderCopy(renderer, objTexture, nullptr, &destRect);
}


void RenderText::updateText(SDL_Renderer* renderer, std::string text)
{
    // Updating text
    this->text = text;

    // Render text onto surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

    // Create texture from surface
    SDL_DestroyTexture(objTexture);
    objTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    // Resize the width of the text
    destRect.w = (text.length())*fontSize/2;

}