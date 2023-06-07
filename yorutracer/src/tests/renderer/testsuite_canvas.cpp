#include <iostream>
#include <assert.h>

#include "tests\testsuite.h"
#include "tests\renderer\testsuite_canvas.h"
#include "renderer\canvas.h"
#include "renderer\screen.h"
#include "renderer\camera.h"
#include "utils.h"

namespace yoru {
namespace test {

	TestSuiteCanvas::TestSuiteCanvas(std::string name) : TestSuite(name)
	{
		add(Test("createCanvas", testsuitecanvas::createCanvas));
		add(Test("createCanvasPoint_ok", testsuitecanvas::createCanvasPoint_ok));
		add(Test("createCanvasPoint_invalid", testsuitecanvas::createCanvasPoint_invalid));
		add(Test("checkPointWorldCoords_origin", testsuitecanvas::checkPointWorldCoords_origin));
		add(Test("checkPointWorldCoords_notorigin", testsuitecanvas::checkPointWorldCoords_notorigin));
		add(Test("checkPointScreenWorldCoords_origin", testsuitecanvas::checkPointScreenWorldCoords_origin));
		add(Test("checkPointScreenWorldCoords_notorigin", testsuitecanvas::checkPointScreenWorldCoords_notorigin));
		add(Test("checkPointScreenCoords_origin", testsuitecanvas::checkPointScreenCoords_origin));
		add(Test("checkPointScreenCoords_notorigin", testsuitecanvas::checkPointScreenCoords_notorigin));
		add(Test("checkPointScreenCoords_differentScale", testsuitecanvas::checkPointScreenCoords_differentScale));
		add(Test("checkPointViewportCoords", testsuitecanvas::checkPointViewportCoords));
	}

	TestSuiteCanvas::~TestSuiteCanvas()
	{
	}

	namespace testsuitecanvas {

		void createCanvas()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, math::Point2d<int>(100, 100));
			int expectedWidth = 200;
			int expectedHeight = 200;
			math::Point2d<int> expectedCenter = math::Point2d<int>(100, 100);

			assert(canvas.getWidth() == expectedWidth && "Wrong canvas width");
			assert(canvas.getHeight() == expectedHeight && "Wrong canvas height");
			assert(canvas.getCenter().getX() == expectedCenter.getX() && canvas.getCenter().getY() == expectedCenter.getY() && "Wrong canvas center");
		}

		void createCanvasPoint_ok()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, math::Point2d<int>(100, 100));

			math::Point2d<int>* canvasPoint = canvas.getPoint(0, 0);
			math::Point2d<int> expectedPoint = math::Point2d<int>(0, 0);

			std::cout << "The canvas point in local coordinates is (" << canvasPoint->getX() << "," << canvasPoint->getY() << ")\n";

			assert(canvasPoint != NULL && "Point is not a valid point in the canvas");
			assert(canvasPoint->getX() == expectedPoint.getX() && canvasPoint->getY() == expectedPoint.getY() && "The canvas point has the wrong coordinates");

			delete canvasPoint;
		}

		void createCanvasPoint_invalid()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, math::Point2d<int>(100, 100));

			// point outside height and width bounds
			math::Point2d<int>* canvasPoint = canvas.getPoint(250, 250);
			assert(canvasPoint == NULL && "Point should be an invalid point in the canvas");

			// point within height and width bounds, but outside height/2 and width/2 bounds
			canvasPoint = canvas.getPoint(150, 150);
			assert(canvasPoint == NULL && "Point should be an invalid point in the canvas");

			delete canvasPoint;
		}

		void checkPointWorldCoords_test(renderer::Canvas, math::Point2d<int>*, math::Point2d<int>);
		void checkPointWorldCoords_origin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, math::Point2d<int>(100, 100));

			math::Point2d<int>* point = canvas.getPoint(0, 0);
			math::Point2d<int> expected = math::Point2d<int>(100, 100);
			checkPointWorldCoords_test(canvas, point, expected);

			delete point;
		}

		void checkPointWorldCoords_notorigin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, math::Point2d<int>(100, 100));

			// both x and y positive
			math::Point2d<int>* point = canvas.getPoint(100, 50);
			math::Point2d<int> expected = math::Point2d<int>(200, 150);
			checkPointWorldCoords_test(canvas, point, expected);

			// x=0 and y positive
			point = canvas.getPoint(0, 50);
			expected = math::Point2d<int>(100, 150);
			checkPointWorldCoords_test(canvas, point, expected);

			// y=0 and x positive
			point = canvas.getPoint(50, 0);
			expected = math::Point2d<int>(150, 100);
			checkPointWorldCoords_test(canvas, point, expected);
			
			// both x and y negative
			point = canvas.getPoint(-100, -50);
			expected = math::Point2d<int>(0, 50);
			checkPointWorldCoords_test(canvas, point, expected);

			delete point;
		}

		void checkPointScreenWorldCoords_test(renderer::Canvas, renderer::Screen, math::Point2d<int>*, math::Point2d<int>);
		void checkPointScreenWorldCoords_origin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, math::Point2d<int>(100, 100));
			renderer::Screen screen = renderer::Screen(200, 200, math::Point2d<int>(-100, 100));

			math::Point2d<int>* point = canvas.getPoint(0, 0);
			math::Point2d<int> expected = math::Point2d<int>(200, 0);
			checkPointScreenWorldCoords_test(canvas, screen, point, expected);

			delete point;
		}

		void checkPointScreenWorldCoords_notorigin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, math::Point2d<int>(100, 100));
			renderer::Screen screen = renderer::Screen(200, 200, math::Point2d<int>(-100, 100));

			// point within the 1st quadrant of the canvas
			math::Point2d<int>* point = canvas.getPoint(100, 50);
			math::Point2d<int> expected = math::Point2d<int>(300, -50);
			checkPointScreenWorldCoords_test(canvas, screen, point, expected);

			// point within the 3rd quadrant of the canvas
			point = canvas.getPoint(-100, -100);
			expected = math::Point2d<int>(100, 100);
			checkPointScreenWorldCoords_test(canvas, screen, point, expected);

			delete point;
		}

		void checkPointScreenCoords_test(renderer::Canvas, renderer::Screen, math::Point2d<int>*, math::Point2d<int>);
		void checkPointScreenCoords_origin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200);
			renderer::Screen screen = renderer::Screen(200, 200);

			math::Point2d<int>* point = canvas.getPoint(0, 0);
			math::Point2d<int> expected = math::Point2d<int>(100, 100);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			delete point;
		}

		void checkPointScreenCoords_notorigin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200);
			renderer::Screen screen = renderer::Screen(200, 200);

			// point within the 1st quadrant of the canvas
			math::Point2d<int>* point = canvas.getPoint(100, 50);
			math::Point2d<int> expected = math::Point2d<int>(200, 50);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			// point within the 2nd quadrant of the canvas
			point = canvas.getPoint(100, -100);
			expected = math::Point2d<int>(200, 200);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			// point within the 3rd quadrant of the canvas
			point = canvas.getPoint(-100, -50);
			expected = math::Point2d<int>(0, 150);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			// point within the 4th quadrant of the canvas
			point = canvas.getPoint(-50, 50);
			expected = math::Point2d<int>(50, 50);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			delete point;
		}

		void checkPointScreenCoords_differentScale()
		{
			// canvas larger than screeen in both width/height
			renderer::Canvas canvas = renderer::Canvas(400, 400);
			renderer::Screen screen = renderer::Screen(200, 200);
			math::Point2d<int>* point = canvas.getPoint(200, 200);
			math::Point2d<int> expected = math::Point2d<int>(200, 0);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			// canvas larger than screen in width only
			canvas = renderer::Canvas(400, 200);
			screen = renderer::Screen(200, 200);
			point = canvas.getPoint(200, 100);
			expected = math::Point2d<int>(200, 0);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			// screen larger than canvas in both width/height
			canvas = renderer::Canvas(200, 200);
			screen = renderer::Screen(400, 400);
			point = canvas.getPoint(100, 100);
			expected = math::Point2d<int>(400, 0);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			// screen larger than canvas in height only
			canvas = renderer::Canvas(200, 200);
			screen = renderer::Screen(200, 400);
			point = canvas.getPoint(100, 0);
			expected = math::Point2d<int>(200, 200);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			delete point;
		}

		void checkPointViewportCoords_test(renderer::Canvas canvas, renderer::Camera camera, math::Point2d<int>* point, math::Point2d<float> expected);
		void checkPointViewportCoords()
		{
			// squared canvas (400x400), squared viewport (1.0x1.0)
			renderer::Canvas canvas = renderer::Canvas(400, 400);
			renderer::Camera camera = renderer::Camera(math::Point3d(10.0f, 0.0f, 0.0f), math::Vector3d(0.0f, 1.0f, 0.0f), math::Vector3d(0.0f, 0.0f, 1.0f), 1.0f, 100.0f, renderer::Viewport(1.0, 1.0));
			math::Point2d<int>* point = canvas.getPoint(200, 200);
			math::Point2d<float> expected = math::Point2d<float>(0.5f, 0.5f);
			checkPointViewportCoords_test(canvas, camera, point, expected);

			// squared canvas (400x400), squared non-unit viewport (2.0x2.0)
			canvas = renderer::Canvas(400, 400);
			camera = renderer::Camera(math::Point3d(10.0f, 0.0f, 0.0f), math::Vector3d(0.0f, 1.0f, 0.0f), math::Vector3d(0.0f, 0.0f, 1.0f), 1.0f, 100.0f, renderer::Viewport(2.0, 2.0));
			point = canvas.getPoint(200, 200);
			expected = math::Point2d<float>(1.0f, 1.0f);
			checkPointViewportCoords_test(canvas, camera, point, expected);

			// 16:9 canvas (1920x1080), 16:9 viewport (1.6x0.9)
			canvas = renderer::Canvas(1920, 1080);
			camera = renderer::Camera(math::Point3d(10.0f, 0.0f, 0.0f), math::Vector3d(0.0f, 1.0f, 0.0f), math::Vector3d(0.0f, 0.0f, 1.0f), 1.0f, 100.0f, renderer::Viewport(1.6, 0.9));
			point = canvas.getPoint(-480, -270);
			expected = math::Point2d<float>(-0.4f, -0.225);
			checkPointViewportCoords_test(canvas, camera, point, expected);

			// 16:9 canvas (1920x1080), squared viewport (1.0x1.0)
			canvas = renderer::Canvas(1920,1080);
			camera = renderer::Camera(math::Point3d(10.0f, 0.0f, 0.0f), math::Vector3d(0.0f, 1.0f, 0.0f), math::Vector3d(0.0f, 0.0f, 1.0f), 1.0f, 100.0f, renderer::Viewport(1.0, 1.0));
			point = canvas.getPoint(-480, -270);
			expected = math::Point2d<float>(-0.25f, -0.25f);
			checkPointViewportCoords_test(canvas, camera, point, expected);

			// squared canvas (800x800), 16:9 viewport (1.6x0.9)
			canvas = renderer::Canvas(800, 800);
			camera = renderer::Camera(math::Point3d(10.0f, 0.0f, 0.0f), math::Vector3d(0.0f, 1.0f, 0.0f), math::Vector3d(0.0f, 0.0f, 1.0f), 1.0f, 100.0f, renderer::Viewport(1.6, 0.9));
			point = canvas.getPoint(200, -200);
			expected = math::Point2d<float>(0.4f, -0.225);
			checkPointViewportCoords_test(canvas, camera, point, expected);

			delete point;
		}

		////////////// tests' core logic functions

		void checkPointWorldCoords_test(renderer::Canvas canvas, math::Point2d<int>* point, math::Point2d<int> expected)
		{
			assert(point != NULL && "Point is not a valid point in the canvas");

			math::Point2d<int> worldPoint = canvas.getCanvasToWorldTransform() * (*point);

			std::cout << "The canvas point in local coordinates is (" << point->getX() << "," << point->getY() << ")\n";
			std::cout << "The canvas point in world coordinates is (" << worldPoint.getX() << "," << worldPoint.getY() << ")\n";

			assert(worldPoint.getX() == expected.getX() && worldPoint.getY() == expected.getY() && "The canvas point has the wrong world space coordinates");
		}

		void checkPointScreenWorldCoords_test(renderer::Canvas canvas, renderer::Screen screen, math::Point2d<int>* point, math::Point2d<int> expected)
		{
			assert(point != NULL && "Point is not a valid point in the canvas");

			math::Point2d<int> screenPoint = canvas.toScreenWorldCoords(*point, screen);

			std::cout << "The canvas point in local coordinates is (" << point->getX() << "," << point->getY() << ")\n";
			std::cout << "The canvas point in screen coordinates is (" << screenPoint.getX() << "," << screenPoint.getY() << ")\n";

			assert(screenPoint.getX() == expected.getX() && screenPoint.getY() == expected.getY() && "The canvas point has the wrong screen space coordinates");
		}

		void checkPointScreenCoords_test(renderer::Canvas canvas, renderer::Screen screen, math::Point2d<int>* point, math::Point2d<int> expected)
		{
			assert(point != NULL && "Point is not a valid point in the canvas");

			math::Point2d<int> screenPoint = canvas.toScreenCoords(*point, screen);

			std::cout << "The canvas point is (" << point->getX() << "," << point->getY() << ")\n";
			std::cout << "The corresponding screen point is (" << screenPoint.getX() << "," << screenPoint.getY() << ")\n";

			assert(screenPoint.getX() == expected.getX() && screenPoint.getY() == expected.getY() && "The canvas point has the wrong screen coordinates");
		}

		void checkPointViewportCoords_test(renderer::Canvas canvas, renderer::Camera camera, math::Point2d<int>* point, math::Point2d<float> expected)
		{
			assert(point != NULL && "Point is not a valid point in the canvas");

			math::Point2d<float> viewportPoint = canvas.toViewportCoords(*point, camera);

			std::cout << "The canvas point is (" << point->getX() << "," << point->getY() << ")\n";
			std::cout << "The corresponding viewport point is (" << viewportPoint.getX() << "," << viewportPoint.getY() << ")\n";

			assert(utils::almostEqual(viewportPoint.getX(), expected.getX(), 0.01) && utils::almostEqual(viewportPoint.getY(), expected.getY(), 0.01) && "The canvas point has the wrong viewport coordinates");
		}
	}
}}

