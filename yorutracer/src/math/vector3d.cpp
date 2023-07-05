#include <math.h>

#include "math\vector3d.h"
#include "math\point3d.h"

namespace yoru {
namespace math {

	Vector3d::Vector3d()
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}

	Vector3d::Vector3d(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3d::~Vector3d()
	{
	}

	float Vector3d::getX() const
	{
		return x;
	}

	float Vector3d::getY() const
	{
		return y;
	}

	float Vector3d::getZ() const
	{
		return z;
	}

	float Vector3d::norm()
	{
		return sqrt(x*x+y*y+z*z);
	}

	void Vector3d::normalize()
	{
		float coef = 1/norm();
		x *= coef;
		y *= coef;
		z *= coef;
	}

	Vector3d Vector3d::cross(const Vector3d& v)
	{
		return Vector3d(this->getY()*v.getZ() - this->getZ()*v.getY(),
						this->getZ()*v.getX() - this->getX()*v.getZ(),
						this->getX()*v.getY() - this->getY()*v.getX());
	}

	float Vector3d::dot(const Vector3d& v)
	{
		return *this * v;
	}

	float operator*(const Vector3d& v1, const Vector3d& v2)
	{
		return v1.getX()*v2.getX() + v1.getY()*v2.getY() + v1.getZ()*v2.getZ();
	}

	Vector3d operator+(const Vector3d& v1, const Vector3d& v2)
	{
		return Vector3d(v1.getX() + v2.getX(), v1.getY() + v2.getY(), v1.getZ() + v2.getZ());
	}

	Vector3d operator*(const Vector3d& v1, float f)
	{
		return Vector3d(v1.getX()*f, v1.getY()*f, v1.getZ()*f);
	}

	Vector3d operator*(float f, const Vector3d& v1)
	{
		return v1*f;
	}

	Vector3d operator-(const Vector3d& v)
	{
		return Vector3d(-v.getX(), -v.getY(), -v.getZ());
	}

	float operator*(const Vector3d& v, const Point3d& p)
	{
		return v.getX()*p.getX() + v.getY()*p.getY() + v.getZ()*p.getZ();
	}

	bool operator==(const Vector3d& v1, const Vector3d& v2)
	{
		return (v1.getX() == v2.getX())
			&& (v1.getY() == v2.getY())
			&& (v1.getZ() == v2.getZ());
	}

	std::ostream& operator<<(std::ostream& out, const Vector3d& v)
	{
		out << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")" << std::endl;

		return out;
	}
}}
