#include <iostream>
#include <assert.h>

#include "math\point.h"
#include "tests\test.h"
#include "tests\renderer\testsuite_screen.h"
#include "renderer\screen.h"
#include "renderer\canvas.h"

namespace yoru {
namespace test {

	TestSuiteScreen::TestSuiteScreen(std::string name) : TestSuite(name)
	{
		add(Test("createScreen", testsuitescreen::createScreen));
		add(Test("createScreenPoint_ok", testsuitescreen::createScreenPoint_ok));
		add(Test("createScreenPoint_invalid", testsuitescreen::createScreenPoint_invalid));
		add(Test("checkPointWorldCoords_origin", testsuitescreen::checkPointWorldCoords_origin));
		add(Test("checkPointWorldCoords_notorigin", testsuitescreen::checkPointWorldCoords_notorigin));
		add(Test("checkPointCanvasWorldCoords_origin", testsuitescreen::checkPointCanvasWorldCoords_origin));
		add(Test("checkPointCanvasWorldCoords_notorigin", testsuitescreen::checkPointCanvasWorldCoords_notorigin));
		add(Test("checkPointCanvasCoords_origin", testsuitescreen::checkPointCanvasCoords_origin));
		add(Test("checkPointCanvasCoords_notorigin", testsuitescreen::checkPointCanvasCoords_notorigin));
		add(Test("checkPointCanvasCoords_differentScale", testsuitescreen::checkPointCanvasCoords_differentScale));
	}

	TestSuiteScreen::~TestSuiteScreen()
	{
	}

	namespace testsuitescreen {

		void createScreen()
		{
			renderer::Screen screen = renderer::Screen(200, 200, yorumathpoint::Point2i(100, 100));
			int expectedWidth = 200;
			int expectedHeight = 200;
			yorumathpoint::Point2i expectedCenter = yorumathpoint::Point2i(100, 100);

			assert(screen.getWidth() == expectedWidth && "Wrong screen width");
			assert(screen.getHeight() == expectedHeight && "Wrong screen height");
			assert(screen.getCenter().getX() == expectedCenter.getX() && screen.getCenter().getY() == expectedCenter.getY() && "Wrong screen center");
		}

		void createScreenPoint_ok()
		{
			renderer::Screen screen = renderer::Screen(200, 200, yorumathpoint::Point2i(100, 100));

			yorumathpoint::Point2i* screenPoint = screen.getPoint(0, 0);
			yorumathpoint::Point2i expectedPoint = yorumathpoint::Point2i(0, 0);

			std::cout << "The screen point in local coordinates is (" << screenPoint->getX() << "," << screenPoint->getY() << ")\n";

			assert(screenPoint != NULL && "Point is not a valid point in the screen");
			assert(screenPoint->getX() == expectedPoint.getX() && screenPoint->getY() == expectedPoint.getY() && "The screen point has the wrong coordinates");

			delete screenPoint;
		}

		void createScreenPoint_invalid()
		{
			renderer::Screen screen = renderer::Screen(200, 200, yorumathpoint::Point2i(100, 100));

			yorumathpoint::Point2i* screenPoint = screen.getPoint(250, 250);
			assert(screenPoint == NULL && "Point should be an invalid point in the screen");

			delete screenPoint;
		}

		void checkPointWorldCoords_test(renderer::Screen, yorumathpoint::Point2i*, yorumathpoint::Point2i);
		void checkPointWorldCoords_origin()
		{
			renderer::Screen screen = renderer::Screen(200, 200, yorumathpoint::Point2i(100, 100));

			yorumathpoint::Point2i* point = screen.getPoint(0, 0);
			yorumathpoint::Point2i expected = yorumathpoint::Point2i(100, 100);
			checkPointWorldCoords_test(screen, point, expected);

			delete point;
		}

		void checkPointWorldCoords_notorigin()
		{
			// screen in the 1st quadrant of the world coordinate system
			renderer::Screen screen = renderer::Screen(200, 200, yorumathpoint::Point2i(100, 100));
			yorumathpoint::Point2i* point = screen.getPoint(100, 100);
			yorumathpoint::Point2i expected = yorumathpoint::Point2i(200, 0);
			checkPointWorldCoords_test(screen, point, expected);
			
			// screen in the 2nd quadrant of the world coordinate system
			screen = renderer::Screen(200, 200, yorumathpoint::Point2i(50, -100));
			point = screen.getPoint(100, 50);
			expected = yorumathpoint::Point2i(150, -150);
			checkPointWorldCoords_test(screen, point, expected);

			// screen in the 3rd quadrant of the world coordinate system
			screen = renderer::Screen(200, 200, yorumathpoint::Point2i(-100, -50));
			point = screen.getPoint(150, 50);
			expected = yorumathpoint::Point2i(50, -100);
			checkPointWorldCoords_test(screen, point, expected);

			// screen in the 4th quadrant of the world coordinate system
			screen = renderer::Screen(200, 200, yorumathpoint::Point2i(-100, 100));
			point = screen.getPoint(100, 50);
			expected = yorumathpoint::Point2i(0, 50);
			checkPointWorldCoords_test(screen, point, expected);

			delete point;
		}

		void checkPointCanvasWorldCoords_test(renderer::Canvas, renderer::Screen, yorumathpoint::Point2i*, yorumathpoint::Point2i);
		void checkPointCanvasWorldCoords_origin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, yorumathpoint::Point2i(100, 100));
			renderer::Screen screen = renderer::Screen(200, 200, yorumathpoint::Point2i(-100, 100));

			yorumathpoint::Point2i* point = screen.getPoint(0, 0);
			yorumathpoint::Point2i expected = yorumathpoint::Point2i(-200, 0);
			checkPointCanvasWorldCoords_test(canvas, screen, point, expected);

			delete point;
		}

		void checkPointCanvasWorldCoords_notorigin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, yorumathpoint::Point2i(100, 100));
			renderer::Screen screen = renderer::Screen(200, 200, yorumathpoint::Point2i(-100, 100));

			yorumathpoint::Point2i* point = screen.getPoint(100, 50);
			yorumathpoint::Point2i expected = yorumathpoint::Point2i(-100, -50);
			checkPointCanvasWorldCoords_test(canvas, screen, point, expected);

			delete point;
		}

		void checkPointCanvasCoords_test(renderer::Canvas, renderer::Screen, yorumathpoint::Point2i*, yorumathpoint::Point2i);
		void checkPointCanvasCoords_origin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200);
			renderer::Screen screen = renderer::Screen(200, 200);

			yorumathpoint::Point2i* point = screen.getPoint(0, 0);
			yorumathpoint::Point2i expected = yorumathpoint::Point2i(-100, 100);
			checkPointCanvasCoords_test(canvas, screen, point, expected);

			delete point;
		}
		
		void checkPointCanvasCoords_notorigin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200);
			renderer::Screen screen = renderer::Screen(200, 200);

			// x=0, y positive
			yorumathpoint::Point2i* point = screen.getPoint(0, 100);
			yorumathpoint::Point2i expected = yorumathpoint::Point2i(-100, 0);
			checkPointCanvasCoords_test(canvas, screen, point, expected);

			// y=0, x positive
			point = screen.getPoint(50, 0);
			expected = yorumathpoint::Point2i(-50, 100);
			checkPointCanvasCoords_test(canvas, screen, point, expected);

			// x and y positive
			point = screen.getPoint(150, 150);
			expected = yorumathpoint::Point2i(50, -50);
			checkPointCanvasCoords_test(canvas, screen, point, expected);

			delete point;
		}

		void checkPointCanvasCoords_differentScale()
		{
			// screen larger than canvas in both width/height
			renderer::Screen screen = renderer::Screen(400, 400);
			renderer::Canvas canvas = renderer::Canvas(200, 200);
			yorumathpoint::Point2i* point = screen.getPoint(200, 200);
			yorumathpoint::Point2i expected = yorumathpoint::Point2i(0, 0);
			checkPointCanvasCoords_test(canvas, screen, point, expected);

			// screen larger than canvas in width only
			screen = renderer::Screen(400, 200);
			canvas = renderer::Canvas(200, 200);
			point = screen.getPoint(300, 100);
			expected = yorumathpoint::Point2i(50, 0);
			checkPointCanvasCoords_test(canvas, screen, point, expected);

			// canvas larger than screen in both width/height
			screen = renderer::Screen(200, 200);
			canvas = renderer::Canvas(400, 400);
			point = screen.getPoint(200, 150);
			expected = yorumathpoint::Point2i(200, -100);
			checkPointCanvasCoords_test(canvas, screen, point, expected);

			// canvas larger than screen in height only
			screen = renderer::Screen(200, 200);
			canvas = renderer::Canvas(200, 400);
			point = screen.getPoint(100, 0);
			expected = yorumathpoint::Point2i(0, 200);
			checkPointCanvasCoords_test(canvas, screen, point, expected);

			delete point;
		}

		////////////// tests' core logic functions

		void checkPointWorldCoords_test(renderer::Screen screen, yorumathpoint::Point2i* point, yorumathpoint::Point2i expected)
		{
			assert(point != NULL && "Point is not a valid point in the screen");

			yorumathpoint::Point2i worldPoint = screen.getScreenToWorldTransform() * (*point);

			std::cout << "The screen point in local coordinates is (" << point->getX() << "," << point->getY() << ")\n";
			std::cout << "The screen point in world coordinates is (" << worldPoint.getX() << "," << worldPoint.getY() << ")\n";

			assert(worldPoint.getX() == expected.getX() && worldPoint.getY() == expected.getY() && "The screen point has the wrong world space coordinates");
		}

		void checkPointCanvasWorldCoords_test(renderer::Canvas canvas, renderer::Screen screen, yorumathpoint::Point2i* point, yorumathpoint::Point2i expected)
		{
			assert(point != NULL && "Point is not a valid point in the canvas");

			yorumathpoint::Point2i canvasPoint = screen.toCanvasWorldCoords(*point, canvas);

			std::cout << "The screen point in local coordinates is (" << point->getX() << "," << point->getY() << ")\n";
			std::cout << "The screen point in canvas coordinates is (" << canvasPoint.getX() << "," << canvasPoint.getY() << ")\n";

			assert(canvasPoint.getX() == expected.getX() && canvasPoint.getY() == expected.getY() && "The screen point has the wrong canvas space coordinates");
		}

		void checkPointCanvasCoords_test(renderer::Canvas canvas, renderer::Screen screen, yorumathpoint::Point2i* point, yorumathpoint::Point2i expected)
		{
			assert(point != NULL && "Point is not a valid point in the screen");

			yorumathpoint::Point2i canvasPoint = screen.toCanvasCoords(*point, canvas);

			std::cout << "The screen point is (" << point->getX() << "," << point->getY() << ")\n";
			std::cout << "The corresponding canvas point is (" << canvasPoint.getX() << "," << canvasPoint.getY() << ")\n";

			assert(canvasPoint.getX() == expected.getX() && canvasPoint.getY() == expected.getY() && "The canvas point has the wrong screen coordinates");
		}
	}
}}
