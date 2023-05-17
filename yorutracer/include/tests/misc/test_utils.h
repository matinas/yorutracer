#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <glm\vec3.hpp>
#include <glm\vec2.hpp>

namespace yorutracer {
namespace tests {

	void test_canvas_to_viewport();
	void test_canvas_to_screen();

	void glm_major_convention_tests();
}
}

#endif
