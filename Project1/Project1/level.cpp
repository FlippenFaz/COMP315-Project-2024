//created by Daniel Hogg
//beware circular dependancies, if you see error C2061: syntax error: identifier 'levelTracker for example, look for circular dependancies
// still need implementation for: question extraction, question display, transitioning between levels(cutscene), add any you can think of...
#include "level.h"
#include "GameObject.h"

level::level() {};

void level::update() {

}

//for rendering level specific objects(not for rendering the background, for now)
void level::render() {

}

void level::incrementQuestionsAnswered() {
	this->questionsAnswered++;
}

void level::levelEndCheck() {
	
}

//having issues here with the pointers, feel free to help. particularly, issue with backGround which is a reference to the pointer, back, in the game class. Gets passed to setBackground
//which is ment to then change back in game class to a new background but currently the screen is just black
void level::setLevel(levelTracker*& trackerr, GameObject*& backGround, GameObject*& player, SDL_Renderer*& renderer) {
	this->tracker = trackerr;
	this->player = player;
	setInitialPosPlayer(player);
	setBackground(backGround);

}

void level::setInitialPosPlayer(GameObject*& player) {

}

void level::setBackground(GameObject*& backGround) {

}

void level::answeringQuestion() {

}
//method for updating the player score maybe