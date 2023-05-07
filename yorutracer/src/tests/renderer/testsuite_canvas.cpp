#include <iostream>
#include <assert.h>

#include "tests\testsuite.h"
#include "tests\renderer\testsuite_canvas.h"
#include "renderer\canvas.h"
#include "renderer\screen.h"

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
	}

	TestSuiteCanvas::~TestSuiteCanvas()
	{
	}

	namespace testsuitecanvas {

		void createCanvas()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, math::Point2d(100, 100));
			int expectedWidth = 200;
			int expectedHeight = 200;
			math::Point2d expectedCenter = math::Point2d(100, 100);

			assert(canvas.getWidth() == expectedWidth && "Wrong canvas width");
			assert(canvas.getHeight() == expectedHeight && "Wrong canvas height");
			assert(canvas.getCenter().getX() == expectedCenter.getX() && canvas.getCenter().getY() == expectedCenter.getY() && "Wrong canvas center");
		}

		void createCanvasPoint_ok()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, math::Point2d(100, 100));

			math::Point2d* canvasPoint = canvas.getPoint(0, 0);
			math::Point2d expectedPoint = math::Point2d(0, 0);

			std::cout << "The canvas point in local coordinates is (" << canvasPoint->getX() << "," << canvasPoint->getY() << ")\n";

			assert(canvasPoint != NULL && "Point is not a valid point in the canvas");
			assert(canvasPoint->getX() == expectedPoint.getX() && canvasPoint->getY() == expectedPoint.getY() && "The canvas point has the wrong coordinates");

			delete canvasPoint;
		}

		void createCanvasPoint_invalid()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, math::Point2d(100, 100));

			// point outside height and width bounds
			math::Point2d* canvasPoint = canvas.getPoint(250, 250);
			assert(canvasPoint == NULL && "Point should be an invalid point in the canvas");

			// point within height and width bounds, but outside height/2 and width/2 bounds
			canvasPoint = canvas.getPoint(150, 150);
			assert(canvasPoint == NULL && "Point should be an invalid point in the canvas");

			delete canvasPoint;
		}

		void checkPointWorldCoords_test(renderer::Canvas, math::Point2d*, math::Point2d);
		void checkPointWorldCoords_origin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, math::Point2d(100, 100));

			math::Point2d* point = canvas.getPoint(0, 0);
			math::Point2d expected = math::Point2d(100, 100);
			checkPointWorldCoords_test(canvas, point, expected);

			delete point;
		}

		void checkPointWorldCoords_notorigin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, math::Point2d(100, 100));

			// both x and y positive
			math::Point2d* point = canvas.getPoint(100, 50);
			math::Point2d expected = math::Point2d(200, 150);
			checkPointWorldCoords_test(canvas, point, expected);

			// x=0 and y positive
			point = canvas.getPoint(0, 50);
			expected = math::Point2d(100, 150);
			checkPointWorldCoords_test(canvas, point, expected);

			// y=0 and x positive
			point = canvas.getPoint(50, 0);
			expected = math::Point2d(150, 100);
			checkPointWorldCoords_test(canvas, point, expected);
			
			// both x and y negative
			point = canvas.getPoint(-100, -50);
			expected = math::Point2d(0, 50);
			checkPointWorldCoords_test(canvas, point, expected);

			delete point;
		}

		void checkPointScreenWorldCoords_test(renderer::Canvas, renderer::Screen, math::Point2d*, math::Point2d);
		void checkPointScreenWorldCoords_origin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, math::Point2d(100, 100));
			renderer::Screen screen = renderer::Screen(200, 200, math::Point2d(-100, 100));

			math::Point2d* point = canvas.getPoint(0, 0);
			math::Point2d expected = math::Point2d(200, 0);
			checkPointScreenWorldCoords_test(canvas, screen, point, expected);

			delete point;
		}

		void checkPointScreenWorldCoords_notorigin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, math::Point2d(100, 100));
			renderer::Screen screen = renderer::Screen(200, 200, math::Point2d(-100, 100));

			// point within the 1st quadrant of the canvas
			math::Point2d* point = canvas.getPoint(100, 50);
			math::Point2d expected = math::Point2d(300, -50);
			checkPointScreenWorldCoords_test(canvas, screen, point, expected);

			// point within the 3rd quadrant of the canvas
			point = canvas.getPoint(-100, -100);
			expected = math::Point2d(100, 100);
			checkPointScreenWorldCoords_test(canvas, screen, point, expected);

			delete point;
		}

		void checkPointScreenCoords_test(renderer::Canvas, renderer::Screen, math::Point2d*, math::Point2d);
		void checkPointScreenCoords_origin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200);
			renderer::Screen screen = renderer::Screen(200, 200);

			math::Point2d* point = canvas.getPoint(0, 0);
			math::Point2d expected = math::Point2d(100, 100);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			delete point;
		}

		void checkPointScreenCoords_notorigin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200);
			renderer::Screen screen = renderer::Screen(200, 200);

			// point within the 1st quadrant of the canvas
			math::Point2d* point = canvas.getPoint(100, 50);
			math::Point2d expected = math::Point2d(200, 50);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			// point within the 2nd quadrant of the canvas
			point = canvas.getPoint(100, -100);
			expected = math::Point2d(200, 200);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			// point within the 3rd quadrant of the canvas
			point = canvas.getPoint(-100, -50);
			expected = math::Point2d(0, 150);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			// point within the 4th quadrant of the canvas
			point = canvas.getPoint(-50, 50);
			expected = math::Point2d(50, 50);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			delete point;
		}

		void checkPointScreenCoords_differentScale()
		{
			// canvas larger than screeen in both width/height
			renderer::Canvas canvas = renderer::Canvas(400, 400);
			renderer::Screen screen = renderer::Screen(200, 200);
			math::Point2d* point = canvas.getPoint(200, 200);
			math::Point2d expected = math::Point2d(200, 0);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			// canvas larger than screen in width only
			canvas = renderer::Canvas(400, 200);
			screen = renderer::Screen(200, 200);
			point = canvas.getPoint(200, 100);
			expected = math::Point2d(200, 0);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			// screen larger than canvas in both width/height
			canvas = renderer::Canvas(200, 200);
			screen = renderer::Screen(400, 400);
			point = canvas.getPoint(100, 100);
			expected = math::Point2d(400, 0);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			// screen larger than canvas in height only
			canvas = renderer::Canvas(200, 200);
			screen = renderer::Screen(200, 400);
			point = canvas.getPoint(100, 0);
			expected = math::Point2d(200, 200);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			delete point;
		}

		////////////// tests' core logic functions

		void checkPointWorldCoords_test(renderer::Canvas canvas, math::Point2d* point, math::Point2d expected)
		{
			assert(point != NULL && "Point is not a valid point in the canvas");

			math::Point2d worldPoint = canvas.getCanvasToWorldTransform() * (*point);

			std::cout << "The canvas point in local coordinates is (" << point->getX() << "," << point->getY() << ")\n";
			std::cout << "The canvas point in world coordinates is (" << worldPoint.getX() << "," << worldPoint.getY() << ")\n";

			assert(worldPoint.getX() == expected.getX() && worldPoint.getY() == expected.getY() && "The canvas point has the wrong world space coordinates");
		}

		void checkPointScreenWorldCoords_test(renderer::Canvas canvas, renderer::Screen screen, math::Point2d* point, math::Point2d expected)
		{
			assert(point != NULL && "Point is not a valid point in the canvas");

			math::Point2d screenPoint = canvas.toScreenWorldCoords(*point, screen);

			std::cout << "The canvas point in local coordinates is (" << point->getX() << "," << point->getY() << ")\n";
			std::cout << "The canvas point in screen coordinates is (" << screenPoint.getX() << "," << screenPoint.getY() << ")\n";

			assert(screenPoint.getX() == expected.getX() && screenPoint.getY() == expected.getY() && "The canvas point has the wrong screen space coordinates");
		}

		void checkPointScreenCoords_test(renderer::Canvas canvas, renderer::Screen screen, math::Point2d* point, math::Point2d expected)
		{
			assert(point != NULL && "Point is not a valid point in the canvas");

			math::Point2d screenPoint = canvas.toScreenCoords(*point, screen);

			std::cout << "The canvas point is (" << point->getX() << "," << point->getY() << ")\n";
			std::cout << "The corresponding screen point is (" << screenPoint.getX() << "," << screenPoint.getY() << ")\n";

			assert(screenPoint.getX() == expected.getX() && screenPoint.getY() == expected.getY() && "The canvas point has the wrong screen coordinates");
		}
	}
}}

