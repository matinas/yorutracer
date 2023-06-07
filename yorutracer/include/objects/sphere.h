#ifndef SPHERE_H
#define SPHERE_H

#include <glm\vec3.hpp>

#include "objects\intersections\rayintersectioninfo.h"

namespace yoru {
	namespace objects {

class Sphere
{
	private:
		glm::vec3 center;
		float radius;

	public:
		Sphere();
		Sphere(glm::vec3 center, float radius);
		~Sphere();

		glm::vec3 get_center();
		float get_radius();
		
		RayIntersectionInfo intersect(Ray r);
};
	}
}

#endif
