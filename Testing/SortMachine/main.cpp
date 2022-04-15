#include "SortMachine.h"
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
	ifstream inputFile("test.txt");
	string line;
	map<char, int> frequency;
	vector<int> words;
	map<char, int>::iterator mapItr;
	int index;

	SortMachine sorter = SortMachine();

	//check that file opened
	if (!inputFile.is_open()) {
		cout << "could not open file";
		getline(cin, line);
		return 1;
	}

	//while file still has lines in it
	while (getline(inputFile, line)) {
		//get frequencies and word counts in lines
		frequency = sorter.getLetterFrequencies(line);
		words = sorter.getWordLengths(line);

		//create iterator for frequency
		mapItr = frequency.begin();

		//for every word in words
		for (int word : words) {
			//loop for each letter in that word
			for (index = 0; index < word; index++) {
				//if current index of iterator is empty move to next index
				if (mapItr->second <= 0) {
					mapItr++;
				}

				//print out the key of the current iterator index and then decrease value
				cout << mapItr->first;
				mapItr->second--;
			}
			//print space between words
			cout << " ";
		}
		//end line
		cout << endl;
	}

	//keep console up
	getline(cin, line);
	return 1;
}