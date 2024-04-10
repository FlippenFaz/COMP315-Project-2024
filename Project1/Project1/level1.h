#pragma once
#include "level.h"
//Daniel Hogg(created),
//very basic implementation of a level's class to test the level class and the levelTracker class, can be used as an example of how to implement the basic features every level needs 

//forward declaration
class GameObject;

//level1 class extending level class
class level1: public level
{

public: 

	level1();

	//override in derived classes(each level class)
	void update();

	//override in derived classes(each level class)
	//void render();

	//override in derived classes(each level class)
	void setInitialPosPlayer(GameObject*& player);

	//override in derived classes(each level class)
	void setBackground(GameObject*& backGround);

	//override in derived classes(each level class)
	void levelEndCheck();

	//increment questions answered if bullet hits target
	void answeringQuestion();

	//void clean();

};

