#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

#pragma once

using namespace std;
struct SortMachine
{
public:
	SortMachine();
	~SortMachine();
	map<char, int> getLetterFrequencies(string input);
	map<char, int> transformVowels(string input);
	vector<int> getWordLengths(string input);
	string inMorse(string input);
	bool isWhiteSpace(char input);
	string uselessFunction(string input);

private:
	bool isUpperVowel(char input);
};