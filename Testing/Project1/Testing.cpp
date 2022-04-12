#include "Testing.h"

struct Testing
{
public:
	Testing();
	~Testing();
	int doSomething(int input);

};

int Testing::doSomething(int input) {
	return input * 2;
}

Testing::Testing()
{
}

Testing::~Testing()
{
}