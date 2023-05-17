#include <glm/glm.hpp>
#include <glm/mat2x2.hpp>
#include <iostream>

#include "utils.h"

using namespace yorutracer::utils;

namespace yorutracer {
namespace tests {

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

		glm::vec2 s_coords = canvas_to_screen_custom(pixel, glm::vec2(CANVAS_WIDTH, CANVAS_HEIGHT));
		std::cout << "Screen coordinates: (" << s_coords.x << ", " << s_coords.y << ")" << std::endl;
	}

	void glm_major_convention_tests()
	{
		glm::mat2x2 m1 = glm::mat2x2(1.0f, 2.0f,
									 3.0f, 4.0f);

		std::cout << "m1_00=" << m1[0][0] << ", m1_01=" << m1[0][1] << std::endl; // strangely, accessing the elements in row-major order gives us 
		std::cout << "m1_10=" << m1[1][0] << ", m1_11=" << m1[1][1] << std::endl; // the expected results despite glm uses a column-major layout...

		glm::vec2 p1(1,1);
		glm::vec2 v = m1 * p1;
		std::cout << "(" << v.x << "," << v.y << ")" << std::endl; // do not return the expected result as we are post-multiplying when glm expects to pre-multiply

		glm::mat2x2 m1_trans = glm::transpose(m1);
		v = m1_trans * p1;
		std::cout << "(" << v.x << "," << v.y << ")" << std::endl; // returns the expected result as we are post-multiplying, after applying the transpose of the matrix

		glm::vec2 row0 = glm::vec2(1.0f, 2.0f);
		glm::vec2 row1 = glm::vec2(3.0f, 4.0f);

		glm::mat2x2 m2 = glm::mat2x2(row0, row1);

		std::cout << "m2_00=" << m2[0][0] << ", m2_01=" << m2[0][1] << std::endl;
		std::cout << "m2_10=" << m2[1][0] << ", m2_11=" << m2[1][1] << std::endl;

		glm::mat2x2 m3(10,20,
					   30,40);

		print_matrix_2x2(m1, false);
		print_matrix_2x2(m2, false);
		print_matrix_2x2(m3, false);

		glm::mat2x2 mul = m1 * m3;

		std::cout << "mul_00=" << mul[0][0] << ", mul_01=" << mul[0][1] << std::endl;
		std::cout << "mul_10=" << mul[1][0] << ", mul_11=" << mul[1][1] << std::endl;

		print_matrix_2x2(mul, false);
	}
}
}
