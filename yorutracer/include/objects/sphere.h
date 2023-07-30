#ifndef SPHERE_H
#define SPHERE_H

#include "math\vector.h"
#include "math\matrix\matrix3x3.h"
#include "renderer\raytracer\rayintersectioninfo.h"

namespace yoru {
namespace objects {

	class Sphere
	{
	private:
		yorumathpoint::Point3f center;
		float radius;
		yorumathpoint::Point3f color;

	public:
		Sphere();
		Sphere(const yorumathpoint::Point3f& center, float radius);
		Sphere(const yorumathpoint::Point3f& center, float radius, const yorumathpoint::Point3f& color);
		~Sphere();

		yorumathpoint::Point3f getCenter() const;
		float getRadius() const;
		yorumathpoint::Point3f getColor() const;
		
		renderer::RayIntersectionInfo intersect(const Ray r);

		void transform(math::Matrix3x3* transform);
	};
}}

#endif
