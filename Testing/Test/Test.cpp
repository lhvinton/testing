#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/Testing.cpp"

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
	};
}
