#ifndef RAY_H
#define RAY_H

#include <glm\vec3.hpp>

namespace yorutracer {

class Ray
{
	private:
		glm::vec3 origin;
		glm::vec3 destination;

	public:
		Ray();
		Ray(glm::vec3 origin, glm::vec3 destination);
		~Ray();

		glm::vec3 get_origin();
		glm::vec3 get_destination();
};
}

#endif
