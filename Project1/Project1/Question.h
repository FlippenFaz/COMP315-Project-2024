/*
  Edited by Jaedon Naidu (created),...

  [Add name above after editing]
*/

// Header file for the Question class
#pragma once

#include <string>
using namespace std;


class Question {
private:

	//0 for ABCD, 1 for T/F
	int questionType;

	//Actual question
	string question;

	//A, B, C or D for type 0, True or False for type 1
	string answer;

	//for type 0. Randomly ordered from the 4 options given
	string A;
	string B;
	string C;
	string D;

public:

	Question(string line)
	{
		
	}

	void convert(int questionType, string question, string answer, string wrongAnswers[]) {

	}

	string toString() {

	}

	int countOccurrences(char c, string s) {
		
	}
};
