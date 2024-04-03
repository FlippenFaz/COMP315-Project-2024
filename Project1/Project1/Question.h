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

	//takes in a line as stored in the question textfiles
	Question(string line)
	{
		
	}

	//initiliazes the fields once the values are extracted from the line in the constructor
	void convert(int questionType, string question, string answer, string wrongAnswers[]) {

	}

	//a printout of the question and its options, as well as its correct answer, in a formatted string
	string toString() {

	}

	//helper method to count occurrences of a character in a string
	int countOccurrences(char c, string s) {
		
	}

	//returns correct answer (either A, B, C, D or True, False)
	string getCorrectAnswer()
	{
		
	}
};
