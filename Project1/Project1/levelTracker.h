#pragma once
#include "level2.h"
#include "level1.h"
#include "Login.h"
#include "Leaderboard.h"
//created by Daniel Hogg
// each level/screen will have its own class. Here, the levelTracker class keeps track of which level should currently be displayed using the levelFlags variable.
//Based on the flag, a level's/screen's class can be initialised and returned.

//All this class does is initialise an instance of a specific level/screen based on the flags, return it so that it can be directly accessed(for updating/rendering) in the game class
// and finally provides a function to check if a level needs to be changed to the next level. this is repeatedly checked in the game class update fuinction. flagChangedCheck will return true if
// if flagChanged was set to true. My idea here was that the update function would check if flagChangedCheck was true, if it is then interprateFlag will run which returns an instance 
// of the next level. The level's class would know to set flagChanged to true because there would be a function in each level that counts the number of questions answered
// , when this equals a set number, say 10 questions per level, the levelFlag would be incremented and flagChanged would be set to true.


class levelTracker
{

private:
	int levelFlag;
	bool flagChanged; // set to true initially.
public:

	levelTracker();

	// can set flagChanged to true in each level's class if x number of questions have been answered or if a button is pushed 
	bool flagChangedCheck();

	level* interprateFlag();

	void setLevelFlag(int num);

	int getLevelFlag();

	void incrementLevelFlag();
	
	void setFlagChanged(int flagLevel);

};

