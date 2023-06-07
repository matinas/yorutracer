#ifndef RAY_INTERSECTION_INFO_H
#define RAY_INTERSECTION_INFO_H

#include <glm\vec3.hpp>

#include "ray.h"

namespace yoru {
	namespace objects {

class Sphere;
class RayIntersectionInfo
{
	private:
		Ray* ray;
		Sphere* sphere;

		glm::vec3* points; // intersection points

	public:
		RayIntersectionInfo();
		RayIntersectionInfo(Ray* const ray, Sphere* const sphere, glm::vec3* const points);
		~RayIntersectionInfo();

		Ray* get_ray();
		Sphere* get_sphere();

		bool exist();
		glm::vec3* get_nearest();
		glm::vec3* get_points();
};
	}
}

#endif
