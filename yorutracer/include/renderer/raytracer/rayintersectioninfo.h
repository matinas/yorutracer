#ifndef RAY_INTERSECTION_INFO_H
#define RAY_INTERSECTION_INFO_H

#include "math\point.h"
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
		yorumathpoint::Point3f* points; // intersection points

	public:
		RayIntersectionInfo();
		RayIntersectionInfo(Ray* const ray, objects::Sphere* const sphere, yorumathpoint::Point3f* const points);
		~RayIntersectionInfo();

		Ray* getRay() const;
		objects::Sphere* getSphere() const;

		bool hasHits();
		yorumathpoint::Point3f* getNearest();
		yorumathpoint::Point3f* getPoints();
	};
}};

#endif
