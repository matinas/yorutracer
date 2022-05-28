#ifndef MATH_H
#define MATH_H

#define IMAGE_WIDTH 500
#define IMAGE_HEIGHT 500

#define CANVAS_WIDTH 500
#define CANVAS_HEIGHT 500

#include <glm\vec3.hpp>
#include <glm\vec2.hpp>

namespace yorutracer {
	namespace math {

	glm::vec3 canvas_to_viewport(const glm::vec2 canvas_coord, const glm::vec2 canvas_size, const glm::vec2 viewport_size, float d);
	glm::vec2 canvas_to_screen_glm(const glm::vec2 canvas_coord, const glm::vec2 canvas_size);
	glm::vec2 canvas_to_screen_custom(const glm::vec2 canvas_coord, const glm::vec2 canvas_size);

	}
}

#endif
