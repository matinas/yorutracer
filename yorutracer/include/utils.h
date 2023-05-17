#ifndef UTILS_H
#define UTILS_H

#define MATRIX_3x3_SIZE 9
#define MATRIX_3x3_ROW_SIZE MATRIX_3x3_SIZE/3

#define IMAGE_WIDTH 500
#define IMAGE_HEIGHT 500

#define CANVAS_WIDTH 500
#define CANVAS_HEIGHT 500

#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\mat2x2.hpp>
#include <glm\mat3x3.hpp>

namespace yorutracer {
namespace utils {

	glm::vec3 canvas_to_viewport(const glm::vec2 canvas_coord, const glm::vec2 canvas_size, const glm::vec2 viewport_size, float d);
	glm::vec2 canvas_to_screen_glm(const glm::vec2 canvas_coord, const glm::vec2 canvas_size);
	glm::vec2 canvas_to_screen_custom(const glm::vec2 canvas_coord, const glm::vec2 canvas_size);

	void create_matrix_3x3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22, float* &mat);
	void multiply_mat_3x3(const float* const lmat, const float* const rmat, float* &mult_mat);
	void multiply_vec_3x3(const float* const mat, const glm::vec3 vec, glm::vec3 &prod_mv);
	void print_matrix_3x3(const glm::mat3x3 &mat, bool column_major, bool print_address);
	void print_matrix_2x2(const glm::mat2x2 &mat, bool column_major);
}
}

#endif
