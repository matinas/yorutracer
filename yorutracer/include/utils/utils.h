#ifndef UTILS_H
#define UTILS_H

#define NAMEOF(name) #name // kind of C# nameof(). From https://dev.to/tomoyukiaota/exploring-c-equivalent-of-cs-nameof-operator-1p8c

#include <math.h>

#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\mat2x2.hpp>
#include <glm\mat3x3.hpp>
#include <FreeImage.h>

#include "math\point.h"

namespace yoru {
namespace utils {

	glm::vec3 canvas_to_viewport(const glm::vec2 canvas_coord, const glm::vec2 canvas_size, const glm::vec2 viewport_size, float d);
	glm::vec2 canvas_to_screen_glm(const glm::vec2 canvas_coord, const glm::vec2 canvas_size);
	glm::vec2 canvas_to_screen_custom(const glm::vec2 canvas_coord, const glm::vec2 canvas_size);

	void create_matrix_3x3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22, float* &mat);
	void multiply_mat_3x3(const float* const lmat, const float* const rmat, float* &mult_mat);
	void multiply_vec_3x3(const float* const mat, const glm::vec3 vec, glm::vec3 &prod_mv);
	void print_matrix_3x3(const glm::mat3x3 &mat, bool column_major, bool print_address);
	void print_matrix_2x2(const glm::mat2x2 &mat, bool column_major);

	inline double toDegrees(double radians)
	{
		return radians * (180.0 / M_PI);
	}

	inline double toRadians(double degrees)
	{
		return degrees * (M_PI / 180.0);
	}

	inline bool almostEqual(double a, double b, double epsilon)
	{
		return abs(a-b) <= epsilon;
	}

	inline RGBQUAD toRGBQUAD(const math::Point3f& p)
	{
		RGBQUAD rgb;
		rgb.rgbRed = static_cast<BYTE>(p.getX() * 255);
		rgb.rgbGreen = static_cast<BYTE>(p.getY() * 255);
		rgb.rgbBlue = static_cast<BYTE>(p.getZ() * 255);

		return rgb;
	}
}
}

#endif
