#ifndef SPHERE_H
#define SPHERE_H

#include "math\vector3d.h"
#include "math\matrix\matrix3x3.h"
#include "renderer\raytracer\rayintersectioninfo.h"

namespace yoru {
namespace objects {

	class Sphere
	{
	private:
		math::Point3d center;
		float radius;
		math::Point3d color;

	public:
		Sphere();
		Sphere(const math::Point3d& center, float radius);
		Sphere(const math::Point3d& center, float radius, const math::Point3d& color);
		~Sphere();

		math::Point3d getCenter() const;
		float getRadius() const;
		math::Point3d getColor() const;
		
		renderer::RayIntersectionInfo intersect(const Ray r);

		void transform(math::Matrix3x3* transform);
	};
}}

#endif
