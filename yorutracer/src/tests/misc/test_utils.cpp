#include <glm/glm.hpp>
#include <glm/mat2x2.hpp>
#include <iostream>

#include "utils.h"

using namespace yorutracer;

void glm_major_convention_tests()
{
	glm::mat2x2 m2 = glm::mat2x2(1.0f, 2.0f,
								 3.0f, 4.0f);

	glm::mat2x2 m2_trans = glm::transpose(m2);

	glm::vec2 p1(1,1);
	glm::vec2 v = m2 * p1;

	std::cout << "(" << v.x << "," << v.y << ")" << std::endl;

	glm::mat2x2 m3(10,20,
				   30,40);

	print_matrix_2x2(m2, false);
	print_matrix_2x2(m3, false);

	glm::mat2x2 mul = m2 * m3;

	print_matrix_2x2(mul, false);
}
