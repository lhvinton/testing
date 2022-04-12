#include <string>
#include <map>

#pragma once

using namespace std;
struct SortMachine
{
public:
	SortMachine();
	~SortMachine();
	map<char, int> getLetterFrequencies(string input);
};