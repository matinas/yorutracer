#ifndef RAY_H
#define RAY_H

#include "math\point3d.h"

namespace yoru {

	class Ray
	{
	private:
		math::Point3d origin;
		math::Point3d destination;

	public:
		Ray();
		Ray(const math::Point3d& origin, const math::Point3d& destination);
		~Ray();

		math::Point3d getOrigin() const;
		math::Point3d getDestination() const;
	};
}

#endif
