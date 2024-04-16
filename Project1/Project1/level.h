#pragma once
//#include "Game.h"
//#include "levelTracker.h"
#include "SDL.h"
//created by Daniel Hogg
//Edited by Faran Steenkamp (added virtual destructor)

//each screen/level must extend level, every function in this class is needed in every level
//feel free to add any additional functions that would be useful to be accessable by every level

//forward declarations
class levelTracker;
class GameObject;

class level
{

protected:

	int questionsAnswered = 0;
	int playerPoints;
	levelTracker* tracker;
	SDL_Renderer*  renderer;
	GameObject* player;
	GameObject* back;
	bool playerInvolvmentStatus = true;

	//still need to implement a transition method that gets called when a level ends

public:

	level();
	virtual ~level(); 

	//used to increment questionsAnswered when an event occurs that signifys an answer has been given by the player
	void incrementQuestionsAnswered();

	//void setTracker(levelTracker* tracker);

	//initializes important info required by all levels
	void setLevel(levelTracker*& tracker, GameObject* backGround, GameObject*& player, SDL_Renderer*& renderer);

	bool getPlayerInvolvmentStatus();

	//override in derived classes(each level class)
	//update position/other important variables of moving game objects specific to a level
	virtual void update();

	//override in derived classes(each level class)
	// render objects specific to a level
	virtual void render();
	
	//override in derived classes(each level class)
	//sets the initial position of the player in a level by accessing player object in game class
	virtual void setInitialPosPlayer(GameObject*& player);

	//override in derived classes(each level class)
	// sets the back object in the game class 
	virtual void setBackground();

	//override in derived classes(each level class)
	//checks if the level has ended by checking if questionsAnswered == 10
	virtual void levelEndCheck();

	//override in derived classes(each level class)
	//checks if the bullets position when it was destroyed is an answer to a question
	virtual void answeringQuestion();

	virtual void setPlayerInvolved();

};

