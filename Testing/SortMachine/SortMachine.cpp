#include "SortMachine.h"
#include <iostream>

const char whiteSpaceChars[4] = {' ', '\n', '\t', '\r'};

const map<char, string> morseMap = {
	{'A', ".-"},
	{'B', "-..."},
	{'C', "-.-."},
	{'D', "-.."},
	{'E', "."},
	{'F', "..-."},
	{'G', "--."},
	{'H', "...."},
	{'I', ".."},
	{'J', ".---"},
	{'K', "-.-"},
	{'L', ".-.."},
	{'M', "--"},
	{'N', "-."},
	{'O', "---"},
	{'P', ".--."},
	{'Q', "--.-"},
	{'R', ".-."},
	{'S', "..."},
	{'T', "-"},
	{'U', "..-"},
	{'V', "...-"},
	{'W', ".--"},
	{'X', "-..-"},
	{'Y', "-.--"},
	{'Z', "--.."},
	{'1', ".----"},
	{'2', "..---"},
	{'3', "...--"},
	{'4', "....-"},
	{'5', "....."},
	{'6', "-...."},
	{'7', "--..."},
	{'8', "---.."},
	{'9', "----."},
	{'0', "-----"},
	{'.', ".-.-.-"},
	{',', "--..--"},
	{'?', "..--.."},
	{'\'', ".----."},
	{'!', "-.-.--"},
	{'/', "-..-."},
	{'(', "-.--."},
	{')', "-.--.-"},
	{'&', ".-..."},
	{':', "---..."},
	{';', "-.-.-."},
	{'=', "-...-"},
	{'+', ".-.-."},
	{'-', "-....-"},
	{'_', "..--.-"},
	{'"', ".-..-."},
	{'$', "...-..-"},
	{'@', ".--.-."},
};

SortMachine::SortMachine()
{
}

SortMachine::~SortMachine()
{
}

map<char, int> SortMachine::getLetterFrequencies(string input) {
	map<char, int> frequencies = map<char, int>();

	// remove all whitespace chars
	for (int i = 0; i < *(&whiteSpaceChars + 1) - whiteSpaceChars; i++) {
		input.erase(std::remove(input.begin(), input.end(), whiteSpaceChars[i]), input.end());
	}

	string::iterator stringIt;

	// traverse the string
	for (stringIt = input.begin(); stringIt != input.end(); stringIt++) {
		// add to map
		frequencies[toupper(*stringIt)]++;
	}

	return frequencies;
}

map<char, int> SortMachine::transformVowels(string input) {
	map<char, int> frequencies;
	char vowels[5] = { 'A', 'E', 'I', 'O', 'U' };
	map<char, int>::iterator currentChar;

	frequencies = getLetterFrequencies(input);

	// for each vowel
	for (int i = 0; i < sizeof(vowels); i++) {
		currentChar = frequencies.find(vowels[i]);

		// if map contains vowel
		if (currentChar != frequencies.end()) {
			// add count to that vowel + 1
			frequencies[vowels[i] + 1] += currentChar->second;
			frequencies.erase(currentChar);
		}
	}

	return frequencies;
}

vector<int> SortMachine::getWordLengths(string input) {
	vector<int> wordLengths = {};

	int currentWordSize = 0;
	for (int i = 0; i < input.size(); i++) {

		// determine if current char is white space
		bool isWhiteSpace = SortMachine::isWhiteSpace(input[i]);

		// if current char is not white space, increment word size
		if (!isWhiteSpace) {
			currentWordSize++;

		// if current char is white space and word preceeded it, add word to vector & reset
		} else if (currentWordSize != 0 && input[i] == ' ') {
			wordLengths.push_back(currentWordSize);
			currentWordSize = 0;
		}
	}

	// edge case for if a string does not end in white space
	if (currentWordSize != 0) {
		wordLengths.push_back(currentWordSize);
	}

	if (wordLengths.empty()) {
		wordLengths = { 0 };
	}

	return wordLengths;
}

string SortMachine::inMorse(string input) {
	char previousChar = ' ';
	string finalString = "";
	vector<string> individualLetters = {};
	vector<int> wordBreaks = {};

	for (int i = 0; i < input.size(); i++) {
		char currentCar = toupper(input[i]);
		auto iter = morseMap.find(currentCar);
		if (SortMachine::isWhiteSpace(currentCar)) {
			if (!SortMachine::isWhiteSpace(previousChar)) {
				wordBreaks.push_back(i);
				//individualLetters.push_back("/");
			}
		}
		else if (iter == morseMap.end()) {
			individualLetters.push_back("" + currentCar);
		}
		else {
			individualLetters.push_back("" + iter->second);
		}
		previousChar = currentCar;		
	}

	sort(individualLetters.begin(), individualLetters.end());

	// instert slashes
	for (int index : wordBreaks) {
		auto itPos = individualLetters.begin() + index;
		auto newIt = individualLetters.insert(itPos, "/");
	}

	for (string str : individualLetters) {
		finalString += str + " ";
	}

	// trim trailing space
	finalString.pop_back();

	return finalString;
}

bool SortMachine::isUpperVowel(char input) {
	return (input == 'A' || input == 'E' || input == 'I'
		|| input == 'O' || input == 'U');
}

bool SortMachine::isWhiteSpace(char input) {
	for (int i = 0; i < size(whiteSpaceChars); i++) {
		if (input == whiteSpaceChars[i]) {
			return true;
		}
	}
	return false;
}

string SortMachine::uselessFunction(string input) {
	string finalString = "";

	auto letters = getLetterFrequencies(input);
	auto words = getWordLengths(input);
	auto iter = letters.begin();

	while (iter != letters.end()) {

		for (int j = 0; j < iter->second; j++) {
			if (words[0] == 0) {
				words.erase(words.begin());
				finalString += " ";
			}
			finalString += iter->first;
			words[0]--;
		}
		iter++;
	}

	return finalString;
}