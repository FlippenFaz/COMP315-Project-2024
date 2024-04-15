#include "level1.h"
#include "GameObject.h"


level1::level1() {}

//broken
void level1::setBackground() {
	
	back->setObjTexture("assets/lvl1TestBackground.png");
	
}

void level1::levelEndCheck() {
	if (level::questionsAnswered == 2) {
		//tells update function in game class to update the level
		level::tracker->setFlagChanged(true);
		//sets the level flag to the next level's level flag
		tracker->setLevelFlag(3);
	}
}

void level1::setInitialPosPlayer(GameObject*& player) {
	player->setXPos(-50);
	player->setYPos(128);
}

void level1::answeringQuestion() {
	if (player->getBulletXPos() >= 900) {
		this->incrementQuestionsAnswered();
		//check if the level is done
		this->levelEndCheck();
	}
}

void level1::update() {
	if (player->getBulletDestroyed()) {
		this->answeringQuestion();
		//sets it back to false
		player->setBulletDestroyed();
	}
}

void level1::setPlayerInvolved() {
	this->playerInvolvmentStatus = true;
}