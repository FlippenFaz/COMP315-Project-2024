/*
  Edited by Jaedon Naidu (created),...
  Edited by Faran Steenkamp (answers now stored in vector as opposed to 4 seperate strings, also changed all function declarations to prototypes)
  [Add name above after editing]
*/

// Header file for the Question class
#pragma once

#include <string>
#include <vector>
using namespace std;


class Question {
private:

	//0 for ABCD, 1 for T/F
	int questionType;

	//Actual question
	string question;

	//A, B, C or D for type 0, True or False for type 1
	string correctAnswer;

	//for type 0. Randomly ordered from the 4 options given
	vector<string> answers;

public:

	Question();

	//takes in a line as stored in the question textfiles
	Question(string line);

	//initiliazes the fields once the values are extracted from the line in the constructor
	void convert(int questionType, string question, string correctAnswer, string wrongAnswers[]);

	//a printout of the question and its options, as well as its correct answer, in a formatted string
	string toString();

//	vector<Question> readQuestionsFromFile(const string& filename);

	//helper method to count occurrences of a character in a string
	int countOccurrences(char c, string s);

	//Method to check if an answer is correct
	//Added by Faran, replaced a getter function that returned the correct answer directly
	bool checkAnswer(string ans);

	// Render the questions on screen.
	void render();
};

