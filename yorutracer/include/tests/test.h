#ifndef TEST_H
#define TEST_H

#include <string>

namespace yoru {
namespace test {

	class Test
	{
	public:
		Test(std::string name, void(*func)());
		~Test();

		void run();
	private:
		std::string name;
		void(*testFunc)();
	};
}}

#endif
