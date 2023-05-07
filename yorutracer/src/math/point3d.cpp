#include "math\point3d.h"

namespace yoru {
namespace math {

	Point3d::Point3d()
	{
		this->x = 0;
		this->y = 0;
	}

	Point3d::Point3d(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Point3d::~Point3d()
	{
	}

	float Point3d::getX() const
	{
		return x;
	}

	float Point3d::getY() const
	{
		return y;
	}

	float Point3d::getZ() const
	{
		return z;
	}
}}