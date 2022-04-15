#include "SortMachine.h"
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
	ifstream inputFile;
	string line;
	string args;

	SortMachine sorter = SortMachine();

	cout << "Enter input file: ";
	getline(cin, args);

	inputFile.open(args);
	//check that file opened
	if (!inputFile.is_open()) {
		cout << "could not open file";
		getline(cin, line);
		return 1;
	}

	cout << "Enter mode: ";
	getline(cin, args);

	if (args == "morse" || args == "m")
		while(getline(inputFile, line))
			cout << sorter.inMorse(line) << endl;
	else
		while (getline(inputFile, line))
			cout << sorter.uselessFunction(line) << endl;
	
	//keep console up
	getline(cin, line);
	return 1;
}