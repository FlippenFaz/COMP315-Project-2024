#pragma once
#include "level.h"

//created by Daniel Hogg
//basic level2 class implementation

class GameObject;

class level2: public level
{
public:

	level2();

	//level2(typename levelTracker* trackerr, GameObject &background) ;

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


};

