#ifndef TESTSUITE_CANVAS_H
#define TESTSUITE_CANVAS_H

#include "tests\testsuite.h"

namespace yoru {
namespace test {

	namespace testsuitecanvas
	{
		void createCanvas();
		void createCanvasPoint_ok();
		void createCanvasPoint_invalid();
		void checkPointWorldCoords_origin();
		void checkPointWorldCoords_notorigin();
		void checkPointScreenWorldCoords_origin();
		void checkPointScreenWorldCoords_notorigin();
		void checkPointScreenCoords_origin();
		void checkPointScreenCoords_notorigin();
		void checkPointScreenCoords_differentScale();
		void checkPointViewportCoords();
	}

	class TestSuiteCanvas : public TestSuite
	{
	public:
		TestSuiteCanvas(std::string name);
		~TestSuiteCanvas();
	private:
	};
}}

#endif
