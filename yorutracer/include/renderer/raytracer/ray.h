#ifndef RAY_H
#define RAY_H

#include "math\point.h"
#include "math\matrix\matrix3x3.h"

namespace yoru {

	class Ray
	{
	private:
		yorumathpoint::Point3f origin;
		yorumathpoint::Point3f destination;

	public:
		Ray();
		Ray(const yorumathpoint::Point3f& origin, const yorumathpoint::Point3f& destination);
		~Ray();

		yorumathpoint::Point3f getOrigin() const;
		yorumathpoint::Point3f getDestination() const;
	};
}

#endif
