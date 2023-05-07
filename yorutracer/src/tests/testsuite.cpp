#include <iostream>

#include "tests\testsuite.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

namespace yoru {
namespace test {

	TestSuite::TestSuite(std::string name)
	{
		this->name = name;
	}

	TestSuite::~TestSuite()
	{
	}

	void TestSuite::add(Test test)
	{
		this->tests.push_back(test);
	}

	void TestSuite::run()
	{
		std::cout << this->name << "::test suite started\n\n";

		// switch to this when moving to C++14
		/*for each (Test test in this->tests)
		{
			test.run();
		}*/
		for (std::list<Test>::iterator it = this->tests.begin(); it != this->tests.end(); ++it)
		{
			Test test = *it;
			test.run();
		}

		std::cout << '\n';
		std::cout << this->name << "::test suite completed\n\n";
	}
}}
