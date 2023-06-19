#ifndef RAY_INTERSECTION_INFO_H
#define RAY_INTERSECTION_INFO_H

#include "math\point3d.h"
#include "ray.h"

namespace yoru {
namespace objects {
	class Sphere;
}

namespace renderer {
	
	class RayIntersectionInfo
	{
	private:
		Ray* ray;
		objects::Sphere* sphere;
		math::Point3d* points; // intersection points

	public:
		RayIntersectionInfo();
		RayIntersectionInfo(Ray* const ray, objects::Sphere* const sphere, math::Point3d* const points);
		~RayIntersectionInfo();

		Ray* getRay() const;
		objects::Sphere* getSphere() const;

		bool hasHits();
		math::Point3d* getNearest();
		math::Point3d* getPoints();
	};
}};

#endif
