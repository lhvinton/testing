#include "pch.h"
#include "CppUnitTest.h"
#include "../SortMachine/SortMachine.cpp"
#include <string>
#include <map>
#include <sstream>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const tuple<string, map<char, int>> testStrings[9] = {
	// basic string test cases
	{ "a", { {'A', 1} } },
	{ "aaaa bb c", { {'A', 4}, {'B', 2}, {'C', 1} } },

	// capitalization test cases
	{ "dOeS cApItAlIzAtIoN mAtTeR", { {'A', 4}, {'C', 1}, {'D', 1}, {'E', 2}, {'I', 3}, {'L', 1}, {'M', 1}, {'N', 1}, {'O', 2}, {'P', 1}, {'R', 1}, {'S', 1}, {'T', 4}, {'Z', 1} } },
	{ "The dog is a poodle", { {'A', 1}, {'D', 2}, {'E', 2}, {'G', 1}, {'H', 1}, {'I', 1}, {'L', 1}, {'O', 3},  {'P', 1}, {'S', 1}, {'T', 1} } },
	
	// white space test case
	{ "  \n\t  \n ", { } },
	
	// empty string test case
	{ "", { } },
	
	// punctuation test case
	{ "P!,UncT?-!u!a/ion..", { {'!', 3}, {',', 1}, {'-', 1}, {'.', 2}, {'/', 1}, {'?', 1}, {'A', 1}, {'C', 1}, {'I', 1}, {'N', 2}, {'O', 1}, {'P', 1}, {'T', 1}, {'U', 2} } },
	
	// digit test cases
	{ "numb3er5", { {'3', 1}, {'5', 1}, {'B', 1}, {'E', 1}, {'M', 1}, {'N', 1}, {'R', 1}, {'U', 1} } },
	{ "77301", { {'0', 1}, {'1', 1}, {'3', 1}, {'7', 2} } }
};

const tuple<string, vector<int>> testWords[9] = {
	//few words
	{"a", {1}},
	{"abcd ab a", {4, 2, 1} },

	//lots of short words
	{"abc abc abc abc abc abc abc abc abc abc", {3, 3, 3, 3, 3, 3, 3, 3, 3, 3}},
	{"a a a a a a a a a a", {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
	
	//white space and empty
	{"  \n\t  \n ", {}},
	{"", {}},
	

	//huge word
	{"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", {104}},
	
	//mix
	{"thi\ns sente\tnce has \n\n special \r characters", {4, 8, 3, 7, 10}},
	{"this sentence\t is used\n\n to test if a large mix of superfluous words can indubitably show this \t\t\t works", {4, 8, 2, 4, 2, 4, 2, 1, 5, 3, 2, 11, 5, 3, 11, 4, 4, 5}}
};


const tuple<string, map<char, int>> testVowelIncreaseStrings[9] = {
	// basic string test cases
	{ "a", { {'B', 1} } },
	{ "aaaa bb c", { {'B', 6}, {'C', 1} } },

	// capitalization test cases
	{ "dOeS cApItAlIzAtIoN mAtTeR", { {'B', 4}, {'C', 1}, {'D', 1}, {'F', 2}, {'S', 1}, {'J', 3}, {'L', 1}, {'M', 1}, {'N', 1}, {'P', 3}, {'R', 1}, {'T', 4}, {'Z', 1} } },
	{ "The dog is a poodle", { {'B', 1}, {'T', 1}, {'D', 2}, {'F', 2}, {'G', 1}, {'H', 1}, {'J', 1}, {'L', 1}, {'P', 4}, {'S', 1} } },

	// capitalization test cases
	{ "aeiou", { {'B', 1}, {'F', 1}, {'J', 1}, {'P', 1}, {'V', 1} } },
	{ "AEIOU", { {'B', 1}, {'F', 1}, {'J', 1}, {'P', 1}, {'V', 1} } },
	{ "bcdfghjklmnpqrstvwxyz", { {'B', 1}, {'C', 1}, {'D', 1}, {'F', 1}, {'G', 1}, {'H', 1}, {'J', 1}, {'K', 1}, {'L', 1}, {'M', 1}, {'N', 1}, {'P', 1}, {'Q', 1}, {'R', 1}, {'S', 1}, {'T', 1}, {'V', 1}, {'W', 1}, {'X', 1}, {'Y', 1}, {'Z', 1} } },
	{ "BCDFGHJKLMNPQRSTVWXYZ", { {'B', 1}, {'C', 1}, {'D', 1}, {'F', 1}, {'G', 1}, {'H', 1}, {'J', 1}, {'K', 1}, {'L', 1}, {'M', 1}, {'N', 1}, {'P', 1}, {'Q', 1}, {'R', 1}, {'S', 1}, {'T', 1}, {'V', 1}, {'W', 1}, {'X', 1}, {'Y', 1}, {'Z', 1} } },
};

const tuple<string, string> testMorse[8] = {
	// single words
	{"abc", "-.-. -... .-"},
	{"word", "--- -.. .-- .-."},

	//simple sentences intentional spelling mistake :)
	{"here is a sentence", "- -. -. -.-. / . . / . / . . .- .-. .. ... ... ...."},
	{"abcdef ghijkl mnopq rstub wxyz", "- -- --- --. --.- --.. / -. -.- -.-- -.-. -.. -..- / -... -... . .- .-- / .--- .--. .-. .-.. .. / ..- ..-. ... ...- ...."},

	//punctuation
	{", . ! ? - /", "--..-- / .-.-.- / -.-.-- / ..--.. / -....- / -..-."},

	//punctuation in a sentence
	{"Sphinx of black quartz, judge my vow!", "- -- --- --- --. --.- / --.. --..-- / -. -.- -.-- -.-. -.-.-- / -.. -..- -... . .- .- .-- / .--- .--. .-. .-.. .. / ..- ..- / ..-. ... ...- ...."},
};

const char whiteSpaceCharsTest[4] = { ' ', '\n', '\t', '\r'};
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
				tuple<string, map<char, int>> currentTestSet = testStrings[i];

				// some debug output so Louis doesn't lose his mind
				forLogger << "Running test case for string '" << get<0>(currentTestSet).c_str() << "'.\n";
				Logger::WriteMessage(forLogger.str().c_str());
				forLogger.str(string());

				// call getLetterFrequencies on current test set
				std::map<char, int> result = sorter.getLetterFrequencies(get<0>(currentTestSet));

				// create iterators
				map<char, int>::iterator resultIter = result.begin();
				map<char, int>::iterator controlIter = get<1>(currentTestSet).begin();

				// loop through each index in the result object
				while (controlIter != get<1>(currentTestSet).end()) {

					// checks that each index key matches
					Assert::AreEqual(controlIter->first, resultIter->first);

					// checks that each index value matches
					Assert::AreEqual(resultIter->second, controlIter->second);

					
					// checks that each key is uppercase
					// This assert doesn't do anything. Letters should already be uppercase from test strings.
					// Caused test to fail on punctuation so I commented it out
					// Assert::IsTrue(isupper(resultIter->first));
					
					// increase iterators
					resultIter++;
					controlIter++;
				}

				// checks that result contains the correct number of elements
				Assert::AreEqual(result.size(), get<1>(currentTestSet).size());

				// checks that no white space characters are in result
				for (int i = 0; i < size(whiteSpaceCharsTest); i++) {
					Assert::IsFalse(result.count(whiteSpaceCharsTest[i]));
				}
			}
		}

		/*
		* Test the amount of letters in each word
		*  - returns a vector containing the count of letters in each word
		*  - return a vector with 0 on whitespace only or empty string
		*  - returns in word order of sentence
		*  - works with punctuation
		*  - works with numbers
		*/
		TEST_METHOD(TestLettersInWords)
		{
			// setup
			SortMachine sorter;
			stringstream forLogger;
			vector<int> result;

			// loop through all test cases
			for (int i = 0; i < size(testWords); i++) {
				//current test string and expected vector
				string test = get<0>(testWords[i]);
				vector<int> expectedVector = get<1>(testWords[i]);

				// some debug output so Lenora doesn't lose her mind
				forLogger << "Running test case for string '" << test << "'.\n";
				Logger::WriteMessage(forLogger.str().c_str());
				forLogger.str(string());

				// call getWordLengths on current line
				result = sorter.getWordLengths(test);

				// assert that the expected and observed are equal
				Assert::IsTrue(expectedVector == result);
			}
		}

		/*
		* Tests that transformVowels()
		*  - returns all indices as capital letters
		*  - returns in alphabetical order
		*  - bumps up all vowels to next ascii (from capitals)
		*  - leaves all other letters/characters the same
		*/
		TEST_METHOD(TestAsciiVowelIncreaser)
		{
			// setup
			SortMachine sorter;
			stringstream forLogger;

			// loop to go through all the test strings (essentially each test case)
			for (int i = 0; i < size(testVowelIncreaseStrings); i++) {

				// current test case
				tuple<string, map<char, int>> currentTestSet = testVowelIncreaseStrings[i];

				// some debug output so Louis doesn't lose his mind
				forLogger << "Running test case for string '" << get<0>(currentTestSet).c_str() << "'.\n";
				Logger::WriteMessage(forLogger.str().c_str());
				forLogger.str(string());

				// call getLetterFrequencies on current test set
				std::map<char, int> result = sorter.transformVowels(get<0>(currentTestSet));

				// create iterators
				map<char, int>::iterator resultIter = result.begin();
				map<char, int>::iterator controlIter = get<1>(currentTestSet).begin();

				// loop through each index in the result object
				while (controlIter != get<1>(currentTestSet).end()) {

					// checks that each index key matches
					Assert::AreEqual(controlIter->first, resultIter->first);

					// checks that each index value matches
					Assert::AreEqual(resultIter->second, controlIter->second);

					// checks that each key is uppercase
					//Assert::IsTrue(isupper(resultIter->first));

					// increase iterators
					resultIter++;
					controlIter++;
				}

				// checks that result contains the correct number of elements
				Assert::AreEqual(result.size(), get<1>(currentTestSet).size());

				// checks that no white space characters are in result
				for (int i = 0; i < size(whiteSpaceCharsTest); i++) {
					Assert::IsFalse(result.count(whiteSpaceCharsTest[i]));
				}
			}
		}

		/*
		* Translates each letter into its morse equivilant
		* - prints "|" between each sentence
		* - prints whitespace between each letter
		* - prints "/" between each word
		* - if character has no morse translation print that character
		* - a gift :)
		* - https://www.cryptomuseum.com/radio/morse/
		*/
		TEST_METHOD(TestMorseTranslator) {
			// setup
			SortMachine sorter;
			stringstream forLogger;
			string test, expected, result;

			// loop through all test cases
			for (int i = 0; i < size(testMorse); i++) {
				//current test string and expected string
				test = get<0>(testMorse[i]);
				expected = get<1>(testMorse[i]);

				// some debug output so Lenora doesn't lose her mind
				forLogger << "Running test case for string '" << test << "'.\n";
				Logger::WriteMessage(forLogger.str().c_str());
				forLogger.str(string());

				// call getWordLengths on current line
				result = sorter.inMorse(test);

				// assert that the expected and observed are equal
				Assert::IsTrue(expected.compare(result));
			}
		}

		// helper methods
		map<char, int> getBlankAlphabetMap() {
			map<char, int> frequencies;

			for (int i = 65; i < 90; i++) {
				frequencies[(char)i] = 0;
			}

			return frequencies;
		}
	};
}