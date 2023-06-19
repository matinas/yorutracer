#ifndef SPHERE_H
#define SPHERE_H

#include "math\vector3d.h"
#include "renderer\raytracer\rayintersectioninfo.h"

namespace yoru {
namespace objects {

	class Sphere
	{
	private:
		math::Point3d center;
		float radius;

	public:
		Sphere();
		Sphere(const math::Point3d& center, float radius);
		~Sphere();

		math::Point3d getCenter() const;
		float getRadius() const;
		
		renderer::RayIntersectionInfo intersect(const Ray r);
	};
}}

#endif
