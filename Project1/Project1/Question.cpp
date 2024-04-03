/*
  Created by Jaedon Naidu

  Edited by Jaedon Naidu(created)
  Edited by Jaedon Naidu(methods: constructor, convert, toString, countOccurences)

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

	//Constructor takes on a line in the following format, as stored in the textfiles:
	//	<questionType>$<question>$<correctAnswer>$<incorrectAnswer(s)>
	
	//What we do in the constructor is extract the single line with delimiters into the constituent parts, before calling the convert() method to initialize the fields.
	Question(string line) {
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

	void convert(int questionType, string question, string answer, string wrongAnswers[]) {
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

	//just counts the number of occurences of a character in a string
	int countOccurrences(char c, string s) {
		int count = 0;
		for (auto u : s) {
			if (c == u) {
				count++;
			}
		}
		return count;
	}

	//We'd want to check if a user selection is correct so we'd need this
	//For ABCD questions, this returns the letter name (that'll be easier cause the user will be shooting the letter name, not the actual option in text)
	//For T/F questions, this returns "True" or "False"
	string getCorrectAnswer()
	{
		return this->answer;
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
};
