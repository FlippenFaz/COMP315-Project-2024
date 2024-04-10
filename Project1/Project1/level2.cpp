#include "level2.h"
#include "GameObject.h"
//created by Daniel Hogg

level2::level2() {}

//broken
void level2::setBackground(GameObject*& backGround) {
	
	backGround->setObjTexture("assets/lvl2TestBackground");
	
	// *backGround = new GameObject("assets/lvl2TestBackground", this->renderer, 0, 0, 1);
}

void level2::levelEndCheck() {
	if (questionsAnswered == 10) {
		//tells update function in game class to update the level
		tracker->setFlagChanged(true);
		//sets the level flag to the next level's level flag
		tracker->setLevelFlag(2);
	}
}

void level2::setInitialPosPlayer(GameObject*& player) {
	player->setXPos(-50);
	player->setYPos(128);
}

void level2::answeringQuestion() {
	if (player->getBulletXPos() >= 900) {
		this->incrementQuestionsAnswered();
		//check if the level is done
		this->levelEndCheck();
	}
}

void level2::update() {
	if (player->getBulletDestroyed()) {
		this->answeringQuestion();
		//sets it back to false
		player->setBulletDestroyed();
	}
}
