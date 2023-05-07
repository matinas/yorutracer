#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <list>

#include "tests\test.h"

namespace yoru {
namespace test {

	class TestSuite
	{
	public:
		TestSuite(std::string name);
		virtual ~TestSuite() = 0;

		void add(Test test);
		void run();
	private:
		std::string name;
		std::list<Test> tests;
	};
}}

#endif
