#include <iostream>
#include <iomanip>
#include <assert.h>

#include "tests\testsuite.h"
#include "tests\renderer\testsuite_camera.h"
#include "renderer\camera.h"
#include "renderer\viewport.h"
#include "utils\utils.h"

namespace yoru {
namespace test {

	TestSuiteCamera::TestSuiteCamera(std::string name) : TestSuite(name)
	{
		add(Test("createCamera_invalid", testsuitecamera::createCamera_invalid));
		add(Test("createCamera_ok", testsuitecamera::createCamera_ok));
		add(Test("checkFOV_createCameraFromSymmetricalViewport", testsuitecamera::checkFOV_createCameraFromSymmetricalViewport));
		add(Test("checkFOV_createCameraFromAsymmetricalViewport", testsuitecamera::checkFOV_createCameraFromAsymmetricalViewport));
		add(Test("checkViewport_createCameraFromSymmetricalFOV", testsuitecamera::checkViewport_createCameraFromSymmetricalFOV));
		add(Test("checkViewport_createCameraFromAsymmetricalFOV", testsuitecamera::checkViewport_createCameraFromAsymmetricalFOV));
	}

	TestSuiteCamera::~TestSuiteCamera()
	{
	}

	namespace testsuitecamera {

		void checkViewport_createCameraFromFOV_test(renderer::Camera camera, renderer::Viewport expectedViewport);
		void checkCameraBasicSettings_test(renderer::Camera camera, math::Point3d expectedOrigin, math::Vector3d expectedUp, math::Vector3d expectedForward, float expectedNear, float expectedFar, float expectedFovH, float expectedFovV);

		void createCamera_invalid()
		{
			// create camera with invalid near projection plane distance
			yoru::renderer::Camera camera = renderer::Camera(math::Point3d(10.0f, 0.0f, 0.0f), math::Vector3d(0.0f, 1.0f, 0.0f), math::Vector3d(0.0f, 0.0f, 1.0f), -1.0f, yoru::renderer::Camera::DefaultFarPlane, yoru::renderer::Camera::DefaultFovH, yoru::renderer::Camera::DefaultFovV);
			yoru::math::Point3d expectedOrigin = math::Point3d(10.0f, 0.0f, 0.0f);
			yoru::math::Vector3d expectedUp = math::Vector3d(0.0f, 1.0f, 0.0f);
			yoru::math::Vector3d expectedForward = math::Vector3d(0.0f, 0.0f, 1.0f);
			float expectedNear = yoru::renderer::Camera::DefaultNearPlane;
			float expectedFar = yoru::renderer::Camera::DefaultFarPlane;
			float expectedFovH = yoru::renderer::Camera::DefaultFovH;
			float expectedFovV = yoru::renderer::Camera::DefaultFovV;
			checkCameraBasicSettings_test(camera, expectedOrigin, expectedUp, expectedForward, expectedNear, expectedFar, expectedFovH, expectedFovV);

			// create camera with invalid far projection plane distance
			camera = renderer::Camera(math::Point3d(10.0f, 0.0f, 0.0f), math::Vector3d(0.0f, 1.0f, 0.0f), math::Vector3d(0.0f, 0.0f, 1.0f), yoru::renderer::Camera::DefaultNearPlane, -1.0f, yoru::renderer::Camera::DefaultFovH, yoru::renderer::Camera::DefaultFovV);
			checkCameraBasicSettings_test(camera, expectedOrigin, expectedUp, expectedForward, expectedNear, expectedFar, expectedFovH, expectedFovV);

			// create camera with invalid horizontal FOV
			camera = renderer::Camera(math::Point3d(10.0f, 0.0f, 0.0f), math::Vector3d(0.0f, 1.0f, 0.0f), math::Vector3d(0.0f, 0.0f, 1.0f), yoru::renderer::Camera::DefaultNearPlane, yoru::renderer::Camera::DefaultFarPlane, -1.0f, yoru::renderer::Camera::DefaultFovV);
			checkCameraBasicSettings_test(camera, expectedOrigin, expectedUp, expectedForward, expectedNear, expectedFar, expectedFovH, expectedFovV);
			
			// create camera with invalid vertical FOV
			camera = renderer::Camera(math::Point3d(10.0f, 0.0f, 0.0f), math::Vector3d(0.0f, 1.0f, 0.0f), math::Vector3d(0.0f, 0.0f, 1.0f), yoru::renderer::Camera::DefaultNearPlane, yoru::renderer::Camera::DefaultFarPlane, yoru::renderer::Camera::DefaultFovH, -1.0f);
			checkCameraBasicSettings_test(camera, expectedOrigin, expectedUp, expectedForward, expectedNear, expectedFar, expectedFovH, expectedFovV);

			// create camera with invalid viewport
			camera = renderer::Camera(math::Point3d(10.0f, 0.0f, 0.0f), math::Vector3d(0.0f, 1.0f, 0.0f), math::Vector3d(0.0f, 0.0f, 1.0f), 1.0f, 100.0f, renderer::Viewport(-1.0, -1.0));
			expectedFovH = 53.13;
			expectedFovV = 53.13;
			renderer::Viewport expectedViewport = renderer::Viewport(1.0, 1.0);
			checkViewport_createCameraFromFOV_test(camera, expectedViewport); // check that the viewport is properly corrected and set to the defualt
			checkCameraBasicSettings_test(camera, expectedOrigin, expectedUp, expectedForward, expectedNear, expectedFar, expectedFovH, expectedFovV); // check that FOVs are calcualted properly with the new corrected viewport
		}

		void createCamera_ok() // we are not validating proper viewport calculation here, as that's validated in separate tests
		{
			// create camera with default values
			renderer::Camera camera = renderer::Camera();
			math::Point3d expectedOrigin = math::Point3d(0.0f, 0.0f, 0.0f);
			math::Vector3d expectedUp = math::Vector3d(0.0f, 1.0f, 0.0f);
			math::Vector3d expectedForward = math::Vector3d(0.0f, 0.0f, 1.0f);
			float expectedNear = renderer::Camera::DefaultNearPlane;
			float expectedFar = renderer::Camera::DefaultFarPlane;
			float expectedFovH = renderer::Camera::DefaultFovH;
			float expectedFovV = renderer::Camera::DefaultFovV;
			checkCameraBasicSettings_test(camera, expectedOrigin, expectedUp, expectedForward, expectedNear, expectedFar, expectedFovH, expectedFovV);

			// create camera specifying origin, up, and forward vectors (remaining settings with default values)
			camera = renderer::Camera(math::Point3d(10.0f, 0.0f, 0.0f), math::Vector3d(0.0f, 1.0f, 1.0f), math::Vector3d(0.0f, -1.0f, 1.0f));
			expectedOrigin = math::Point3d(10.0f, 0.0f, 0.0f);
			expectedUp = math::Vector3d(0.0f, 1.0f, 1.0f);
			expectedForward = math::Vector3d(0.0f, -1.0f, 1.0f);
			expectedNear = renderer::Camera::DefaultNearPlane;
			expectedFar = renderer::Camera::DefaultFarPlane;
			expectedFovH = renderer::Camera::DefaultFovH;
			expectedFovV = renderer::Camera::DefaultFovV;
			checkCameraBasicSettings_test(camera, expectedOrigin, expectedUp, expectedForward, expectedNear, expectedFar, expectedFovH, expectedFovV);

			// create camera specifying origin, up, and forward vectors, near plane distance, far plane distance, and symmetrical FOV
			camera = renderer::Camera(math::Point3d(10.0f, 0.0f, 0.0f), math::Vector3d(0.0f, 1.0f, 1.0f), math::Vector3d(0.0f, -1.0f, 1.0f), 10.0f, 50.0f, 50.0f);
			expectedOrigin = math::Point3d(10.0f, 0.0f, 0.0f);
			expectedUp = math::Vector3d(0.0f, 1.0f, 1.0f);
			expectedForward = math::Vector3d(0.0f, -1.0f, 1.0f);
			expectedNear = 10.0f;
			expectedFar = 50.0f;
			expectedFovH = 50.0f;
			expectedFovV = 50.0f;
			checkCameraBasicSettings_test(camera, expectedOrigin, expectedUp, expectedForward, expectedNear, expectedFar, expectedFovH, expectedFovV);

			// create camera specifying origin, up, and forward vectors, near plane distance, far plane distance, and assymmetrical FOV horizontal and vertical, respectively
			camera = renderer::Camera(math::Point3d(10.0f, 0.0f, 0.0f), math::Vector3d(0.0f, 1.0f, 1.0f), math::Vector3d(0.0f, -1.0f, 1.0f), 10.0f, 50.0f, 150.0f, 50.0f);
			expectedOrigin = math::Point3d(10.0f, 0.0f, 0.0f);
			expectedUp = math::Vector3d(0.0f, 1.0f, 1.0f);
			expectedForward = math::Vector3d(0.0f, -1.0f, 1.0f);
			expectedNear = 10.0f;
			expectedFar = 50.0f;
			expectedFovH = 150.0f;
			expectedFovV = 50.0f;
			checkCameraBasicSettings_test(camera, expectedOrigin, expectedUp, expectedForward, expectedNear, expectedFar, expectedFovH, expectedFovV);
		}

		void checkViewport_createCameraFromViewport_test(renderer::Camera camera, float expectedFovH, float expectedFovV);
		void checkFOV_createCameraFromSymmetricalViewport()
		{
			renderer::Camera camera = renderer::Camera(math::Point3d(10.0f, 0.0f, 0.0f), math::Vector3d(0.0f, 1.0f, 0.0f), math::Vector3d(0.0f, 0.0f, 1.0f), 1.0f, 100.0f, renderer::Viewport(1.0, 1.0));
			float expectedFovH = 53.13;
			float expectedFovV = 53.13;

			checkViewport_createCameraFromViewport_test(camera, expectedFovH, expectedFovV);
		}

		void checkFOV_createCameraFromAsymmetricalViewport()
		{
			renderer::Camera camera = renderer::Camera(math::Point3d(10.0f, 0.0f, 0.0f), math::Vector3d(0.0f, 1.0f, 0.0f), math::Vector3d(0.0f, 0.0f, 1.0f), 1.0f, 100.0f, renderer::Viewport(1.5, 1.0));
			float expectedFovH = 73.73;
			float expectedFovV = 53.13;

			checkViewport_createCameraFromViewport_test(camera, expectedFovH, expectedFovV);
		}

		void checkViewport_createCameraFromSymmetricalFOV()
		{
			renderer::Camera camera = renderer::Camera(math::Point3d(10.0f, 0.0f, 0.0f), math::Vector3d(0.0f, 1.0f, 0.0f), math::Vector3d(0.0f, 0.0f, 1.0f), 1.0f, 100.0f, 53.13f);
			renderer::Viewport expectedViewport = renderer::Viewport(1.0, 1.0);
			
			checkViewport_createCameraFromFOV_test(camera, expectedViewport);
		}

		void checkViewport_createCameraFromAsymmetricalFOV()
		{
			renderer::Camera camera = renderer::Camera(math::Point3d(10.0f, 0.0f, 0.0f), math::Vector3d(0.0f, 1.0f, 0.0f), math::Vector3d(0.0f, 0.0f, 1.0f), 1.0f, 100.0f, 90.0, 53.0);
			renderer::Viewport expectedViewport = renderer::Viewport(2.0, 1.0);
			
			checkViewport_createCameraFromFOV_test(camera, expectedViewport);
		}

		////////////// tests' core logic functions

		void checkCameraBasicSettings_test(renderer::Camera camera, math::Point3d expectedOrigin, math::Vector3d expectedUp, math::Vector3d expectedForward,
										   float expectedNear, float expectedFar, float expectedFovH, float expectedFovV)
		{
			assert(camera.getOrigin().getX() == expectedOrigin.getX() && camera.getOrigin().getY() == expectedOrigin.getY() && camera.getOrigin().getZ() == expectedOrigin.getZ() && "The camera has the wrong origin point");
			assert(camera.getUp().getX() == expectedUp.getX() && camera.getUp().getY() == expectedUp.getY() && camera.getUp().getZ() == expectedUp.getZ() && "The camera has the wrong up vector");
			assert(camera.getForward().getX() == expectedForward.getX() && camera.getForward().getY() == expectedForward.getY() && camera.getForward().getZ() == expectedForward.getZ() && "The camera has the wrong forward vector");
			assert(utils::almostEqual(camera.getNear(), expectedNear, 0.01f) && "The camera has the wrong near plane distance");
			assert(utils::almostEqual(camera.getFar(), expectedFar, 0.01) && "The camera has the wrong far plane distance");
			assert(utils::almostEqual(camera.getFovH(), expectedFovH, 0.01) && "The camera has the wrong horizontal FOV");
			assert(utils::almostEqual(camera.getFovV(), expectedFovV, 0.01) && "The camera has the wrong vertical FOV");
		}

		void checkViewport_createCameraFromViewport_test(renderer::Camera camera, float expectedFovH, float expectedFovV)
		{
			std::cout << "The horizontal FOV for the camera is " << camera.getFovH() << "\n";
			std::cout << "The vertical FOV for the camera is " << camera.getFovV() << "\n";

			bool fovHCheck = utils::almostEqual(camera.getFovH(), expectedFovH, 0.01);
			bool fovVCheck = utils::almostEqual(camera.getFovV(), expectedFovV, 0.01);

			assert(fovHCheck && "The camera has the wrong horizontal FOV");
			assert(fovVCheck && "The camera has the wrong vertical FOV");
		}

		void checkViewport_createCameraFromFOV_test(renderer::Camera camera, renderer::Viewport expectedViewport)
		{
			std::cout << std::setprecision(2) << "The viewport dimensions are " << camera.getViewport().getWidth() << "x" << camera.getViewport().getHeight() << "\n";

			bool widthCheck = utils::almostEqual(camera.getViewport().getWidth(), expectedViewport.getWidth(), 0.01);
			bool heightCheck = utils::almostEqual(camera.getViewport().getHeight(), expectedViewport.getHeight(), 0.01);

			assert(widthCheck && "The camera has the wrong viewport width");
			assert(heightCheck && "The camera has the wrong viewport height");
		}
	}
}}

