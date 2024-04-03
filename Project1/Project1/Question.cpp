/*
  Created by Jaedon Naidu

  Edited by Jaedon Naidu(created)

  [Add name above after editing]
*/

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

//A class used to model the question
class Question {
private:
	int questionType;
	string question;
	string answer;
	string A;
	string B;
	string C;
	string D;

public:

	/*parameters:   questionType: 0 means ABCD, 1 means T/F
					question: the actual question
					answer: the correct answer
					wrongAnswers[]: an array (of either 3 elements for ABCD or an array of 1 element for T/F)
	*/

	Question(int questionType, string question, string answer, string wrongAnswers[]) {
		this->questionType = questionType;
		this->question = question;
		this->answer = answer;

		//if the question is ABCD then we need to store all options (else just true/false)
		if (questionType == 0) {
			vector<string> buffer;
			buffer.push_back(answer);
			for (int i = 0; i < 3; i++) {
				buffer.push_back(wrongAnswers[i]);
			}

			//mt19937 is a very efficient pseudorandom number generator
			random_device rd;
			mt19937 g(rd());

			//put the options in a random order
			shuffle(buffer.begin(), buffer.end(), g);

			this->A = buffer.at(0);
			this->B = buffer.at(1);
			this->C = buffer.at(2);
			this->D = buffer.at(3);

			//for convenience the answer attribute is set to the correct letter
			for (int i = 0; i < buffer.size(); i++) {
				if (buffer.at(i) == answer) {
					char c = (char)(i + 65);
					this->answer = c;
				}
			}
		}
	}

	string toString() {
		string s = "QUESTION TYPE: " + to_string(this->questionType) + "\n";
		s += "QUESTION: " + this->question + "\n";
		s += "CORRECT ANSWER: " + this->answer + "\n";
		if (this->questionType == 0) {
			s += "A: " + this->A + "\n";
			s += "B: " + this->B + "\n";
			s += "C: " + this->C + "\n";
			s += "D: " + this->D + "\n";
		}
		return s;
	}

	/*SAMPLE INPUT:
	Question* q = new Question(0, "What is 5+5?","10", ["4", "6", "8"]);

	SAMPLE OUTPUT:
	QUESTION TYPE: 0
	QUESTION: What is 5+5?
	CORRECT ANSWER: C
	A: 6
	B: 8
	C: 10
	D: 4

	*/

	/*SAMPLE INPUT:
	Question* q = new Question(1, "True or False: 5+5 = 10?","True", ["False"]);

	SAMPLE OUTPUT:
	QUESTION TYPE: 1
	QUESTION: True or False: 5+5 = 10?
	CORRECT ANSWER: True

	*/
};
