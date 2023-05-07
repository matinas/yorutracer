#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <iostream>

#include "math/math.h"

using namespace yorutracer;
using namespace yorutracer::math;

void test_canvas_to_viewport()
{
	glm::vec2 pixel(-960,540);

	glm::vec3 v_coords = canvas_to_viewport(pixel, glm::vec2(1920,1080), glm::vec2(1,1), 1);

	std::cout << "Canvas coordinates: (" << pixel.x << ", " << pixel.y << ")" << std::endl;
	std::cout << "Viewport coordinates: (" << v_coords.x << ", " << v_coords.y << ", " << v_coords.z << ")" << std::endl;
}

void test_canvas_to_screen()
{
	glm::vec2 pixel(-960,540);

	glm::vec2 s_coords = canvas_to_screen_custom(pixel, glm::vec2(CANVAS_WIDTH,CANVAS_HEIGHT));
	std::cout << "Screen coordinates: (" << s_coords.x << ", " << s_coords.y << ")" << std::endl;
}
	