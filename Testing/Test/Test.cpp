#include "pch.h"
#include "CppUnitTest.h"
#include "../SortMachine/SortMachine.cpp"
#include <string>
#include <map>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const tuple<string, map<char, int>> testStrings[9] = {
	// basic string test cases
	{ "a", { {'A', 1} } },
	{ "aaaa bb c", { {'A', 4}, {'B', 2}, {'C', 1} } },

	// capitalization test cases
	{ "dOeS cApItAlIzAtIoN mAtTeR", { {'D', 1}, {'O', 2}, {'E', 2}, {'S', 1}, {'C', 1}, {'A', 4}, {'P', 1}, {'I', 3}, {'T', 4}, {'L', 1}, {'Z', 1}, {'N', 1}, {'M', 1}, {'R', 1} } },
	{ "The dog is a poodle", { {'T', 1}, {'H', 1}, {'E', 2}, {'D', 2}, {'O', 3}, {'G', 1}, {'I', 1}, {'S', 1}, {'A', 1}, {'P', 1}, {'L', 1} } },
	
	// white space test case
	{ "  \n\t  \n ", { } },
	
	// empty string test case
	{ "", { } },
	
	// punctuation test case
	{ "P!,UncT?-!u!a/ion..", { {'P', 1}, {'!', 3}, {',', 1}, {'U', 2}, {'N', 2}, {'C', 1}, {'T', 1}, {'?', 1}, {'-', 1}, {'A', 1}, {'/', 1}, {'I', 1}, {'O', 1}, {'.', 2} } },
	
	// digit test cases
	{ "numb3er5", { {'N', 1}, {'U', 1}, {'M', 1}, {'B', 1}, {'3', 1}, {'E', 1}, {'R', 1}, {'5', 1} } },
	{ "77301", { {'7', 2}, {'3', 1}, {'0', 1}, {'1', 1} } }
};

const char whiteSpaceChars[3] = { ' ', '\n', '\t' };
namespace Test
{
	TEST_CLASS(Test)
	{
	public:
		/*
		* Tests that getLetterFrequencies()
		*  - returns empty empty string provided
		*  - returns empty when white space only provided
		*  - returns all indices as capital letters
		*  - works with punctuation
		*  - returns in alphabetical order
		*  - works with numbers
		*/
		TEST_METHOD(TestLettersTotal)
		{
			// setup
			SortMachine sorter;
			stringstream forLogger;

			// loop to go through all the test strings (essentially each test case)
			for (int i = 0; i < size(testStrings); i++) {

				// current test case
				auto currentTestSet = testStrings[i];

				// some debug output so Louis doesn't lose his mind
				forLogger << "Running test case for string '" << get<0>(currentTestSet).c_str() << "'.\n";
				Logger::WriteMessage(forLogger.str().c_str());

				// call getLetterFrequencies on current test set
				std::map<char, int> result = sorter.getLetterFrequencies(get<0>(currentTestSet));
				
				// create iterators
				auto resultIter = result.begin();
				auto controlIter = get<1>(currentTestSet).begin();

				// loop through each index in the result object
				while (controlIter != get<1>(currentTestSet).end()) {

					// checks that each index key matches
					Assert::AreEqual(controlIter->first, resultIter->first);

					// checks that each index value matches
					Assert::AreEqual(resultIter->second, controlIter->second);

					// checks that each key is uppercase
					Assert::IsTrue(isupper(resultIter->first));

					// increase iterators
					resultIter++;
					controlIter++;
				}

				// checks that result contains the correct number of elements
				Assert::AreEqual(result.size(), get<1>(currentTestSet).size());

				// checks that no white space characters are in result
				for (int i = 0; i < size(whiteSpaceChars); i++) {
					Assert::IsFalse(result.count(whiteSpaceChars[i]));
				}
			}
		}

		TEST_METHOD(TestLettersInWords)
		{
			//Assert::AreEqual(sorter.lettersInWords(), { 1, 2, 3 });
		}
	};

	// helper methods
	map<char, int> getBlankAlphabetMap() {
		map<char, int> frequencies;

		for (int i = 65; i < 90; i++) {
			frequencies[(char)i] = 0;
		}

		return frequencies;
	}
}


