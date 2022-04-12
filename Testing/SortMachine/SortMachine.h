#include <string>
#include <map>
#include <vector>

#pragma once

using namespace std;
struct SortMachine
{
public:
	SortMachine();
	~SortMachine();
	map<char, int> getLetterFrequencies(string input);
	vector<int> getWordLengths(string input);
};