#include "SortMachine.h"

const char whiteSpaceChars[4] = {' ', '\n', '\t', '\r'};

SortMachine::SortMachine()
{
}

SortMachine::~SortMachine()
{
}

map<char, int> SortMachine::getLetterFrequencies(string input) {
	map<char, int> frequencies;
	return frequencies;
}

map<char, int> SortMachine::transformVowels(string input) {
	map<char, int> frequencies;
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

int main() {
	return 1;
}