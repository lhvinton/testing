#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/Sort.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
	TEST_CLASS(Test)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Testing testingObj;
			Assert::AreEqual(testingObj.doSomething(3), 3 * 2);
		}

		TEST_METHOD(TestLettersInWords)
		{
			int arr1[] = { 1, 2, 3 };
			int arr2[] = { 1, 2, 3 }; //repalce with function
			bool equal;


			if (std::equal(std::begin(arr1), std::end(arr1), std::begin(arr2)))
				equal = true;
			else
				equal = false;
			Assert::IsTrue(equal);
		}
	};
}
