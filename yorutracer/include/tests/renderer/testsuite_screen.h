#ifndef TESTSUITE_SCREEN_H
#define TESTSUITE_SCREEN_H

#include "tests\testsuite.h"

namespace yoru {
namespace test {

	namespace testsuitescreen
	{
		void createScreen();
		void createScreenPoint_ok();
		void createScreenPoint_invalid();
		void checkPointWorldCoords_origin();
		void checkPointWorldCoords_notorigin();
		void checkPointCanvasWorldCoords_origin();
		void checkPointCanvasWorldCoords_notorigin();
		void checkPointCanvasCoords_origin();
		void checkPointCanvasCoords_notorigin();
		void checkPointCanvasCoords_differentScale();
	}

	class TestSuiteScreen : public TestSuite
	{
	public:
		TestSuiteScreen(std::string name);
		~TestSuiteScreen();
	private:
	};
}}

#endif
