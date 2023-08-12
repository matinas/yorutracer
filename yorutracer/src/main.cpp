#define DEBUG 0

#include <iostream>
#include <cstdio>
#include <string>

#include "utils\utils.h"
#include "utils\timer.h"
#include "utils\common.h"

#include "renderer\canvas.h"
#include "renderer\screen.h"
#include "renderer\camera.h"
#include "renderer\raytracer\raytracer.h"

#include "tests\renderer\testsuite_canvas.h"
#include "tests\renderer\testsuite_screen.h"
#include "tests\renderer\testsuite_camera.h"
#include "tests\misc\test_utils.h"

#include "math\vector.h"

using namespace yoru;
using namespace yoru::utils;

enum RunMode
{
	RENDER = 0,
	TEST = 1,
	NONE = -1,	
};

void render();
void runTestSuites();

int main(int argc, char* argv[])
{
	RunMode mode = RunMode::NONE;
    if (argc > 1)
	{
		mode = static_cast<RunMode>(std::stoi(argv[1]));
	}

	switch (mode)
	{
		case RunMode::RENDER:
			render();
			break;
		case RunMode::TEST:
			runTestSuites();
			break;
		default:
			std::cout << "Trying to run with an invalid run mode, please verify\n";
	}

	return EXIT_SUCCESS;
}

void render()
{
	renderer::Canvas canvas = renderer::Canvas(CANVAS_WIDTH, CANVAS_HEIGHT);
	renderer::Screen screen = renderer::Screen(IMAGE_WIDTH, IMAGE_HEIGHT);
	renderer::Camera camera = renderer::Camera(yorumathpoint::Point3f(0.f,0.f,0.f), yorumathvector::Vector3f(0.f,1.f,0.f), yorumathvector::Vector3f(0.f,0.f,1.f), 1.f, 100, renderer::Viewport(1.0,1.0));

	camera.lookAt(yorumathpoint::Point3f(0.0f,0.5f,1.f));

	renderer::Raytracer raytracer = renderer::Raytracer(canvas, screen, camera);

	Timer timer = Timer();
	timer.start();

	raytracer.render();

	timer.stop();
	std::cout << "The rendering process took " << timer.getElapsedTime(Timer::TimeUnit::MILISECONDS) << "ms to complete\n";
}

void runTestSuites()
{
	yoru::test::TestSuiteCanvas testCanvas("TestSuiteCanvas");
	testCanvas.run();

	yoru::test::TestSuiteScreen testScreen("TestSuiteScreen");
	testScreen.run();

	yoru::test::TestSuiteCamera testCamera("TestSuiteCamera");
	testCamera.run();
}
