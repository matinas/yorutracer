#ifndef TESTSUITE_CAMERA_H
#define TESTSUITE_CAMERA_H

#include "tests\testsuite.h"

namespace yoru {
namespace test {

	namespace testsuitecamera
	{
		void createCamera_invalid();
		void createCamera_ok();
		void checkFOV_createCameraFromSymmetricalViewport();
		void checkFOV_createCameraFromAsymmetricalViewport();
		void checkViewport_createCameraFromSymmetricalFOV();
		void checkViewport_createCameraFromAsymmetricalFOV();
	}

	class TestSuiteCamera : public TestSuite
	{
	public:
		TestSuiteCamera(std::string name);
		~TestSuiteCamera();
	private:
	};
}}

#endif
