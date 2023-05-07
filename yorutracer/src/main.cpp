#define DEBUG 0

#include <iostream>
#include <FreeImage.h>

#include "utils.h"
#include "objects/sphere.h"
#include "objects/intersections/rayintersectioninfo.h"
#include "ray.h"
#include "math/math.h"

#include "renderer\canvas.h"
#include "renderer\screen.h"

#include "tests\renderer\testsuite_canvas.h"
#include "tests\renderer\testsuite_screen.h"

RGBQUAD rgb_black = {0,0,0};
RGBQUAD rgb_blue = {255,0,0};

using namespace yorutracer;
using namespace yorutracer::objects;
using namespace yorutracer::math;

int main(char* argv, int argc)
{
	yoru::test::TestSuiteCanvas testCanvas("TestSuiteCanvas");
	testCanvas.run();

	yoru::test::TestSuiteScreen testScreen("TestSuiteScreen");
	testScreen.run();

	return EXIT_SUCCESS;

	//////////////////////////////////////////

	FreeImage_Initialise();

	FIBITMAP *bitmap = FreeImage_Allocate(IMAGE_HEIGHT, IMAGE_WIDTH, 24);

	if (bitmap)
	{
		std::cout << "Bitmap successfully created" << std::endl;
	}
	else
	{
		std::cout << "There was a problem generating bitmap" << std::endl;

		return -1;
	}

	Sphere sphere = Sphere(glm::vec3(0.f,0.f,3.0f),1.0f);
	RGBQUAD rgb;

	for (int i=-CANVAS_WIDTH/2; i<CANVAS_WIDTH/2; ++i)
	{
		for (int j=-CANVAS_HEIGHT/2; j<CANVAS_HEIGHT/2; ++j)
		{
			glm::vec3 viewport_point = canvas_to_viewport(glm::vec2(i,j), glm::vec2(CANVAS_WIDTH,CANVAS_HEIGHT), glm::vec2(1,1), 1.f);
			if (DEBUG) std::cout << "Viewport point: (" << viewport_point.x << "," << viewport_point.y << "," << viewport_point.z << ")" << std::endl;

			glm::vec2 screen = canvas_to_screen_custom(glm::vec2(i,j), glm::vec2(CANVAS_WIDTH,CANVAS_HEIGHT));

			Ray ray = Ray(glm::vec3(0.f), viewport_point);
			RayIntersectionInfo ray_sphere = sphere.intersect(ray);

			if (ray_sphere.exist())
			{
				glm::vec3* point = ray_sphere.get_nearest();

				rgb = rgb_blue;
			}
			else // there's no interesection
			{
				rgb = rgb_black;
			}

			FreeImage_SetPixelColor(bitmap, screen.x, screen.y, &rgb);
		}
	}
	
	if (FreeImage_Save(FIF_JPEG, bitmap, "output.jpeg", 0))
	{
		std::cout << "Bitmap successfully saved!" << std::endl;

		FreeImage_Unload(bitmap);
	}

	return EXIT_SUCCESS;
}
