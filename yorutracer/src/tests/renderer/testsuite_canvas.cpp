#include <iostream>
#include <assert.h>

#include "math\point.h"
#include "math\vector.h"
#include "tests\testsuite.h"
#include "tests\renderer\testsuite_canvas.h"
#include "renderer\canvas.h"
#include "renderer\screen.h"
#include "renderer\camera.h"
#include "utils\utils.h"

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
			renderer::Canvas canvas = renderer::Canvas(200, 200, yorumathpoint::Point2i(100, 100));
			int expectedWidth = 200;
			int expectedHeight = 200;
			yorumathpoint::Point2i expectedCenter = yorumathpoint::Point2i(100, 100);

			assert(canvas.getWidth() == expectedWidth && "Wrong canvas width");
			assert(canvas.getHeight() == expectedHeight && "Wrong canvas height");
			assert(canvas.getCenter().getX() == expectedCenter.getX() && canvas.getCenter().getY() == expectedCenter.getY() && "Wrong canvas center");
		}

		void createCanvasPoint_ok()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, yorumathpoint::Point2i(100, 100));

			yorumathpoint::Point2i* canvasPoint = canvas.getPoint(0, 0);
			yorumathpoint::Point2i expectedPoint = yorumathpoint::Point2i(0, 0);

			std::cout << "The canvas point in local coordinates is (" << canvasPoint->getX() << "," << canvasPoint->getY() << ")\n";

			assert(canvasPoint != NULL && "Point is not a valid point in the canvas");
			assert(canvasPoint->getX() == expectedPoint.getX() && canvasPoint->getY() == expectedPoint.getY() && "The canvas point has the wrong coordinates");

			delete canvasPoint;
		}

		void createCanvasPoint_invalid()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, yorumathpoint::Point2i(100, 100));

			// point outside height and width bounds
			yorumathpoint::Point2i* canvasPoint = canvas.getPoint(250, 250);
			assert(canvasPoint == NULL && "Point should be an invalid point in the canvas");

			// point within height and width bounds, but outside height/2 and width/2 bounds
			canvasPoint = canvas.getPoint(150, 150);
			assert(canvasPoint == NULL && "Point should be an invalid point in the canvas");

			delete canvasPoint;
		}

		void checkPointWorldCoords_test(renderer::Canvas, yorumathpoint::Point2i*, yorumathpoint::Point2i);
		void checkPointWorldCoords_origin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, yorumathpoint::Point2i(100, 100));

			yorumathpoint::Point2i* point = canvas.getPoint(0, 0);
			yorumathpoint::Point2i expected = yorumathpoint::Point2i(100, 100);
			checkPointWorldCoords_test(canvas, point, expected);

			delete point;
		}

		void checkPointWorldCoords_notorigin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, yorumathpoint::Point2i(100, 100));

			// both x and y positive
			yorumathpoint::Point2i* point = canvas.getPoint(100, 50);
			yorumathpoint::Point2i expected = yorumathpoint::Point2i(200, 150);
			checkPointWorldCoords_test(canvas, point, expected);

			// x=0 and y positive
			point = canvas.getPoint(0, 50);
			expected = yorumathpoint::Point2i(100, 150);
			checkPointWorldCoords_test(canvas, point, expected);

			// y=0 and x positive
			point = canvas.getPoint(50, 0);
			expected = yorumathpoint::Point2i(150, 100);
			checkPointWorldCoords_test(canvas, point, expected);
			
			// both x and y negative
			point = canvas.getPoint(-100, -50);
			expected = yorumathpoint::Point2i(0, 50);
			checkPointWorldCoords_test(canvas, point, expected);

			delete point;
		}

		void checkPointScreenWorldCoords_test(renderer::Canvas, renderer::Screen, yorumathpoint::Point2i*, yorumathpoint::Point2i);
		void checkPointScreenWorldCoords_origin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, yorumathpoint::Point2i(100, 100));
			renderer::Screen screen = renderer::Screen(200, 200, yorumathpoint::Point2i(-100, 100));

			yorumathpoint::Point2i* point = canvas.getPoint(0, 0);
			yorumathpoint::Point2i expected = yorumathpoint::Point2i(200, 0);
			checkPointScreenWorldCoords_test(canvas, screen, point, expected);

			delete point;
		}

		void checkPointScreenWorldCoords_notorigin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200, yorumathpoint::Point2i(100, 100));
			renderer::Screen screen = renderer::Screen(200, 200, yorumathpoint::Point2i(-100, 100));

			// point within the 1st quadrant of the canvas
			yorumathpoint::Point2i* point = canvas.getPoint(100, 50);
			yorumathpoint::Point2i expected = yorumathpoint::Point2i(300, -50);
			checkPointScreenWorldCoords_test(canvas, screen, point, expected);

			// point within the 3rd quadrant of the canvas
			point = canvas.getPoint(-100, -100);
			expected = yorumathpoint::Point2i(100, 100);
			checkPointScreenWorldCoords_test(canvas, screen, point, expected);

			delete point;
		}

		void checkPointScreenCoords_test(renderer::Canvas, renderer::Screen, yorumathpoint::Point2i*, yorumathpoint::Point2i);
		void checkPointScreenCoords_origin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200);
			renderer::Screen screen = renderer::Screen(200, 200);

			yorumathpoint::Point2i* point = canvas.getPoint(0, 0);
			yorumathpoint::Point2i expected = yorumathpoint::Point2i(100, 100);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			delete point;
		}

		void checkPointScreenCoords_notorigin()
		{
			renderer::Canvas canvas = renderer::Canvas(200, 200);
			renderer::Screen screen = renderer::Screen(200, 200);

			// point within the 1st quadrant of the canvas
			yorumathpoint::Point2i* point = canvas.getPoint(100, 50);
			yorumathpoint::Point2i expected = yorumathpoint::Point2i(200, 50);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			// point within the 2nd quadrant of the canvas
			point = canvas.getPoint(100, -100);
			expected = yorumathpoint::Point2i(200, 200);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			// point within the 3rd quadrant of the canvas
			point = canvas.getPoint(-100, -50);
			expected = yorumathpoint::Point2i(0, 150);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			// point within the 4th quadrant of the canvas
			point = canvas.getPoint(-50, 50);
			expected = yorumathpoint::Point2i(50, 50);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			delete point;
		}

		void checkPointScreenCoords_differentScale()
		{
			// canvas larger than screeen in both width/height
			renderer::Canvas canvas = renderer::Canvas(400, 400);
			renderer::Screen screen = renderer::Screen(200, 200);
			yorumathpoint::Point2i* point = canvas.getPoint(200, 200);
			yorumathpoint::Point2i expected = yorumathpoint::Point2i(200, 0);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			// canvas larger than screen in width only
			canvas = renderer::Canvas(400, 200);
			screen = renderer::Screen(200, 200);
			point = canvas.getPoint(200, 100);
			expected = yorumathpoint::Point2i(200, 0);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			// screen larger than canvas in both width/height
			canvas = renderer::Canvas(200, 200);
			screen = renderer::Screen(400, 400);
			point = canvas.getPoint(100, 100);
			expected = yorumathpoint::Point2i(400, 0);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			// screen larger than canvas in height only
			canvas = renderer::Canvas(200, 200);
			screen = renderer::Screen(200, 400);
			point = canvas.getPoint(100, 0);
			expected = yorumathpoint::Point2i(200, 200);
			checkPointScreenCoords_test(canvas, screen, point, expected);

			delete point;
		}

		void checkPointViewportCoords_test(renderer::Canvas canvas, renderer::Camera camera, yorumathpoint::Point2i* point, yorumathpoint::Point2f expected);
		void checkPointViewportCoords()
		{
			// squared canvas (400x400), squared viewport (1.0x1.0)
			renderer::Canvas canvas = renderer::Canvas(400, 400);
			renderer::Camera camera = renderer::Camera(yorumathpoint::Point3f(10.0f, 0.0f, 0.0f), yorumathvector::Vector3f(0.0f, 1.0f, 0.0f), yorumathvector::Vector3f(0.0f, 0.0f, 1.0f), 1.0f, 100.0f, renderer::Viewport(1.0, 1.0));
			yorumathpoint::Point2i* point = canvas.getPoint(200, 200);
			yorumathpoint::Point2f expected = yorumathpoint::Point2f(0.5f, 0.5f);
			checkPointViewportCoords_test(canvas, camera, point, expected);

			// squared canvas (400x400), squared non-unit viewport (2.0x2.0)
			canvas = renderer::Canvas(400, 400);
			camera = renderer::Camera(yorumathpoint::Point3f(10.0f, 0.0f, 0.0f), yorumathvector::Vector3f(0.0f, 1.0f, 0.0f), yorumathvector::Vector3f(0.0f, 0.0f, 1.0f), 1.0f, 100.0f, renderer::Viewport(2.0, 2.0));
			point = canvas.getPoint(200, 200);
			expected = yorumathpoint::Point2f(1.0f, 1.0f);
			checkPointViewportCoords_test(canvas, camera, point, expected);

			// 16:9 canvas (1920x1080), 16:9 viewport (1.6x0.9)
			canvas = renderer::Canvas(1920, 1080);
			camera = renderer::Camera(yorumathpoint::Point3f(10.0f, 0.0f, 0.0f), yorumathvector::Vector3f(0.0f, 1.0f, 0.0f), yorumathvector::Vector3f(0.0f, 0.0f, 1.0f), 1.0f, 100.0f, renderer::Viewport(1.6, 0.9));
			point = canvas.getPoint(-480, -270);
			expected = yorumathpoint::Point2f(-0.4f, -0.225);
			checkPointViewportCoords_test(canvas, camera, point, expected);

			// 16:9 canvas (1920x1080), squared viewport (1.0x1.0)
			canvas = renderer::Canvas(1920,1080);
			camera = renderer::Camera(yorumathpoint::Point3f(10.0f, 0.0f, 0.0f), yorumathvector::Vector3f(0.0f, 1.0f, 0.0f), yorumathvector::Vector3f(0.0f, 0.0f, 1.0f), 1.0f, 100.0f, renderer::Viewport(1.0, 1.0));
			point = canvas.getPoint(-480, -270);
			expected = yorumathpoint::Point2f(-0.25f, -0.25f);
			checkPointViewportCoords_test(canvas, camera, point, expected);

			// squared canvas (800x800), 16:9 viewport (1.6x0.9)
			canvas = renderer::Canvas(800, 800);
			camera = renderer::Camera(yorumathpoint::Point3f(10.0f, 0.0f, 0.0f), yorumathvector::Vector3f(0.0f, 1.0f, 0.0f), yorumathvector::Vector3f(0.0f, 0.0f, 1.0f), 1.0f, 100.0f, renderer::Viewport(1.6, 0.9));
			point = canvas.getPoint(200, -200);
			expected = yorumathpoint::Point2f(0.4f, -0.225);
			checkPointViewportCoords_test(canvas, camera, point, expected);

			delete point;
		}

		////////////// tests' core logic functions

		void checkPointWorldCoords_test(renderer::Canvas canvas, yorumathpoint::Point2i* point, yorumathpoint::Point2i expected)
		{
			assert(point != NULL && "Point is not a valid point in the canvas");

			yorumathpoint::Point2i worldPoint = canvas.getCanvasToWorldTransform() * (*point);

			std::cout << "The canvas point in local coordinates is (" << point->getX() << "," << point->getY() << ")\n";
			std::cout << "The canvas point in world coordinates is (" << worldPoint.getX() << "," << worldPoint.getY() << ")\n";

			assert(worldPoint.getX() == expected.getX() && worldPoint.getY() == expected.getY() && "The canvas point has the wrong world space coordinates");
		}

		void checkPointScreenWorldCoords_test(renderer::Canvas canvas, renderer::Screen screen, yorumathpoint::Point2i* point, yorumathpoint::Point2i expected)
		{
			assert(point != NULL && "Point is not a valid point in the canvas");

			yorumathpoint::Point2i screenPoint = canvas.toScreenWorldCoords(*point, screen);

			std::cout << "The canvas point in local coordinates is (" << point->getX() << "," << point->getY() << ")\n";
			std::cout << "The canvas point in screen coordinates is (" << screenPoint.getX() << "," << screenPoint.getY() << ")\n";

			assert(screenPoint.getX() == expected.getX() && screenPoint.getY() == expected.getY() && "The canvas point has the wrong screen space coordinates");
		}

		void checkPointScreenCoords_test(renderer::Canvas canvas, renderer::Screen screen, yorumathpoint::Point2i* point, yorumathpoint::Point2i expected)
		{
			assert(point != NULL && "Point is not a valid point in the canvas");

			yorumathpoint::Point2i screenPoint = canvas.toScreenCoords(*point, screen);

			std::cout << "The canvas point is (" << point->getX() << "," << point->getY() << ")\n";
			std::cout << "The corresponding screen point is (" << screenPoint.getX() << "," << screenPoint.getY() << ")\n";

			assert(screenPoint.getX() == expected.getX() && screenPoint.getY() == expected.getY() && "The canvas point has the wrong screen coordinates");
		}

		void checkPointViewportCoords_test(renderer::Canvas canvas, renderer::Camera camera, yorumathpoint::Point2i* point, yorumathpoint::Point2f expected)
		{
			assert(point != NULL && "Point is not a valid point in the canvas");

			yorumathpoint::Point3f viewportPoint = canvas.toViewportCoords(*point, camera);

			std::cout << "The canvas point is (" << point->getX() << "," << point->getY() << ")\n";
			std::cout << "The corresponding viewport point is (" << viewportPoint.getX() << "," << viewportPoint.getY() << ")\n";

			assert(utils::almostEqual(viewportPoint.getX(), expected.getX(), 0.01) && utils::almostEqual(viewportPoint.getY(), expected.getY(), 0.01) && "The canvas point has the wrong viewport coordinates");
		}
	}
}}

