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

bool level::getPlayerInvolvmentStatus() {
	return playerInvolvmentStatus;
}

//having issues here with the pointers, feel free to help. particularly, issue with backGround which is a reference to the pointer, back, in the game class. Gets passed to setBackground
//which is ment to then change back in game class to a new background but currently the screen is just black
void level::setLevel(levelTracker*& trackerr, GameObject* backGround, GameObject*& player, SDL_Renderer*& renderer) {
	this->tracker = trackerr;
	this->player = player;
	this->back = backGround;
	this->renderer = renderer;
	setInitialPosPlayer(player);
	setBackground();//new GameObject("assets/dndhddd.png", renderer, 0, 0, 1);
	//setBackground(backGround);

}

void level::setInitialPosPlayer(GameObject*& player) {

}

void level::setBackground() {
	
}

void level::answeringQuestion() {

}

void level::setPlayerInvolved() {

}

//method for updating the player score maybe