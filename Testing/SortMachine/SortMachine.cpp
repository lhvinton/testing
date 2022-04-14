#include "SortMachine.h"

const char whiteSpaceChars[4] = {' ', '\n', '\t', '\r'};

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
		bool isWhiteSpace = false;
		for (int j = 0; j < size(whiteSpaceChars); j++) {
			if (input[i] == whiteSpaceChars[j]) {
				isWhiteSpace = true;
				break;
			}
		}

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

	return wordLengths;
}

string SortMachine::inMorse(string input) {
	return "... .... . . ... ....";
}

bool SortMachine::isUpperVowel(char input) {
	return (input == 'A' || input == 'E' || input == 'I'
		|| input == 'O' || input == 'U');
}

int main() {
	return 1;
}