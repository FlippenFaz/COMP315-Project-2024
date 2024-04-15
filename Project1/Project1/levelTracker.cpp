#include "levelTracker.h"
//created by Daniel Hogg

levelTracker::levelTracker() {
	this->levelFlag = 0;
	this->flagChanged = true;
}

bool levelTracker::flagChangedCheck() {
	if (this->flagChanged) {
		this->flagChanged = false;
		return true;
	}
	else {
		return false;
	}
}

level* levelTracker::interprateFlag() {
	if (levelFlag == 0) {
		//login
		Login* login = new  Login();
		return login;
	}
	else if (levelFlag == 1) {
		//leader board
		Leaderboard* leaderBoard = new  Leaderboard();
		return leaderBoard;
	}
	else if (levelFlag == 2) {
		// transition to level 1
		level1* lvl1 = new  level1();
		return lvl1;

	}
	else if (levelFlag == 3) {
		// create an instance of level2 class and return it
		// In the level2 class, sets background, player position, tracks questions answered by the player, creates question objects and renders them to the screen
		level2* lvl2 = new  level2();
		return lvl2;

	}
	else if (levelFlag == 4) {
		//level 3
		level2* lvl2 = new  level2();
		return lvl2;
	}
	else if (levelFlag == 5) {
		//level 4
		level2* lvl2 = new  level2();
		return lvl2;
	}
	//temp, complains that nothing might be returned
	else {
		level2* lvl2 = new  level2();
		return lvl2;
	}
}

void levelTracker::setLevelFlag(int num) {
	this->levelFlag = num;
	this->flagChanged = true;
}

int levelTracker::getLevelFlag() {
	return levelFlag;
}

//incase its better to increment rather than directly set the levelFlag
void levelTracker::incrementLevelFlag() {
	this->levelFlag++;
	this->flagChanged = true;
}

void levelTracker::setFlagChanged(int flagLevel) {
	levelFlag = flagLevel;
}