/*
  Created by Jaedon Naidu

  Edited by Jaedon Naidu(created)
  Edited by Jaedon Naidu(methods: constructor, convert, toString, countOccurences)
  Edited by Faran Steenkamp(edited code to align with header file (see there for edits made)

  [Add name above after editing]
*/

#include "Question.h";
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;



//Constructor takes on a line in the following format, as stored in the textfiles:
//	<questionType>$<question>$<correctAnswer>$<incorrectAnswer(s)>
Question::Question() {

}
	
//What we do in the constructor is extract the single line with delimiters into the constituent parts, before calling the convert() method to initialize the fields.
Question::Question(string line) {
	int questionType;
	string question;
	string answer;

	int count = countOccurrences('$', line);
	int pos;

	//if there are five $ symbols then we have an ABCD question
	if (count == 5) {

		//the algorithm is to:
		//	find the position of the $
		//	store the section until the $ inside the relevant variable
		//	erase the section, including the $, and start again
		questionType = 0;
		line.erase(0, 2);

		pos = line.find('$');
		question = line.substr(0, pos);
		line.erase(0, pos + 1);

		pos = line.find('$');
		answer = line.substr(0, pos);
		line.erase(0, pos + 1);

		string wrongAnswers[3];
		for (int i = 0; i < 2; i++) {
			pos = line.find('$');
			wrongAnswers[i] = line.substr(0, pos);
			line.erase(0, pos + 1);
		}
		wrongAnswers[2] = line;

		//we then call the convert method which initializes the attributes once the extraction from the line has taken place
		convert(questionType, question, answer, wrongAnswers);
	}

	//if there are three $ symbols we have a T/F question
	else if (count == 3) {

		//we use the same algorithm:
		//	find the position of the $
		//	store the section until the $ inside the relevant variable
		//	erase the section, including the $, and start again
		questionType = 1;
		line.erase(0, 2);

		pos = line.find('$');
		question = line.substr(0, pos);
		line.erase(0, pos + 1);

		pos = line.find('$');
		answer = line.substr(0, pos);
		line.erase(0, pos + 1);

		string wrongAnswers[1];
		wrongAnswers[0] = line;

		//similarly, we now call convert
		convert(questionType, question, answer, wrongAnswers);
	}
}

/*parameters:   questionType: 0 means ABCD, 1 means T/F
				question: the actual question
				answer: the correct answer
				wrongAnswers[]: an array (of either 3 elements for ABCD or an array of 1 element for T/F)
*/

void Question::convert(int questionType, string question, string correctAnswer, string wrongAnswers[]) {
	this->questionType = questionType;
	this->question = question;
	this->correctAnswer = correctAnswer;

	//if the question is ABCD then we need to store all options (else just true/false)
	if (questionType == 0) {
		vector<string> buffer;
		buffer.push_back(correctAnswer);
		for (int i = 0; i < 3; i++) {
			buffer.push_back(wrongAnswers[i]);
		}

		//mt19937 is a very efficient pseudorandom number generator
		random_device rd;
		mt19937 g(rd());

		//put the options in a random order
		shuffle(buffer.begin(), buffer.end(), g);

		this->answers = buffer;

		//for convenience the answer attribute is set to the correct letter
		for (int i = 0; i < buffer.size(); i++) {
			if (buffer.at(i) == correctAnswer) {
				//Converts index to letter using ascii with offset of 65 (a)
				char c = (char)(i + 65);
				this->correctAnswer = c;
			}
		}
			
	}
}

//Convert to a string for debugging purposes
string Question::toString() {
	string s = "QUESTION TYPE: " + to_string(this->questionType) + "\n";
	s += "QUESTION: " + this->question + "\n";
	s += "CORRECT ANSWER: " + this->correctAnswer + "\n";
	if (this->questionType == 0) {
		s += "A: " + this->answers[0] + "\n";
		s += "B: " + this->answers[1] + "\n";
		s += "C: " + this->answers[2] + "\n";
		s += "D: " + this->answers[3] + "\n";
	}
	return s;
}

//just counts the number of occurences of a character in a string
int Question::countOccurrences(char c, string s) {
	int count = 0;
	for (auto u : s) {
		if (c == u) {
			count++;
		}
	}
	return count;
}

//We'd want to check if a user selection is correct so we'd need this
//For ABCD questions, this expects the letter name (that'll be easier cause the user will be shooting the letter name, not the actual option in text)
//For T/F questions, this expects "True" or "False"
bool Question::checkAnswer(string inputAnswer)
{
	return inputAnswer.compare(correctAnswer) == 0;
}



/*SAMPLE INPUT:
	Question* q = new Question("0$What is a Juliet spy?$A female spy who seduces for her country$A female spy using \"actress\" as a cover$A woman tricked into being a spy$A male spy who dresses as a woman");

SAMPLE OUTPUT:
	QUESTION TYPE: 0
	QUESTION: What is a Juliet spy?
	CORRECT ANSWER: D
	A: A woman tricked into being a spy
	B: A female spy using "actress" as a cover
	C: A male spy who dresses as a woman
	D: A female spy who seduces for her country

*/

/*SAMPLE INPUT:
	Question* q2 = new Question("1$True/False: Wild Bill Donovan was a famous spymaster seen in a popular series of 1930 movies.$False$True");

SAMPLE OUTPUT:
	QUESTION TYPE: 1
	QUESTION: True/False: Wild Bill Donovan was a famous spymaster seen in a popular series of 1930 movies.
	CORRECT ANSWER: False

*/

//void Question::renderQuestions()
//{
//
//}
