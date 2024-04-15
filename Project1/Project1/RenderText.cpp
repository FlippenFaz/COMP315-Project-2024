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
                width: A requirement for wrapping text, the width must be given for a text display, if its an input then parse 0
                       if the actual width of the text exceeds the width specified then the text is wrapped
*/
RenderText::RenderText(int xpos, int ypos, int fontSize, SDL_Renderer* renderer, std::string text, SDL_Color color, int width)
{
    // Initialize SDL_ttf
    TTF_Init();

    // Store the renderer
    this->renderer = renderer;

    // Load the font by checking how many rows the text will be displayed on (Up to 3 rows)
    // i.e The font is decreased to improve readability of the text when it is wrapped
    if (std::string(text).length() * fontSize / 2 > width*2)
    {
        font = TTF_OpenFont("fonts/DeterminationMono.ttf", fontSize/3);
    }
    else if (std::string(text).length() * fontSize / 2 > width * 2)
    {
        font = TTF_OpenFont("fonts/DeterminationMono.ttf", fontSize/2);
    }
    else
    {
        font = TTF_OpenFont("fonts/DeterminationMono.ttf", fontSize);
    }

    // Render text onto surface
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, width); //goes to next line

    // Create texture from surface
    objTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    // Store the renderer
    this->renderer = renderer;

    // Store the text color
    this->color = color;

    // Store the font size
    this->fontSize = fontSize;

    // Store the text to be displayed
    this->text = text;

    // Set the destination of the rendered text
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = width;
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

// Used for inputting text
void RenderText::updateText(SDL_Renderer* renderer, std::string text)
{
    // Updating text
    this->text = text;

    // Render text onto surface
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, (text.length()) * fontSize / 2);

    // Create texture from surface
    SDL_DestroyTexture(objTexture);
    objTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    // Resize the width of the text
    destRect.w = (text.length())*fontSize/2;

}