#include <iostream>

#include "tests\test.h"

namespace yoru {
namespace test {

	Test::Test(std::string name, void(*testFunc)())
	{
		this->name = name;
		this->testFunc = testFunc;
	}

	Test::~Test()
	{
	}

	void Test::run()
	{
		std::cout << "--- " << this->name << "::test started\n";
		this->testFunc();
		std::cout << "--- " << this->name << "::test completed successfully\n";
	}
}}