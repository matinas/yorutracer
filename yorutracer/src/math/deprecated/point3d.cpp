#include "math\deprecated\point3d.h"
#include "math\deprecated\vector3d.h"

namespace yoru {
namespace math {
namespace deprecated {

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

	Point3d::Point3d(const Point3d& p)
	{
		this->x = p.getX();
		this->y = p.getY();
		this->z = p.getZ();
	}

	Point3d::~Point3d()
	{
	}

	inline float Point3d::getX() const
	{
		return x;
	}

	inline float Point3d::getY() const
	{
		return y;
	}

	inline float Point3d::getZ() const
	{
		return z;
	}

	float Point3d::distanceTo(const Point3d& p)
	{
		return (*this - p).norm();
	}

	bool operator==(const Point3d& p1, const Point3d& p2)
	{
		return p1.getX() == p2.getX() && p1.getY() == p2.getY() && p1.getZ() == p2.getZ();
	}

	Vector3d operator-(const Point3d& p1, const Point3d& p2)
	{
		return Vector3d(p1.getX()-p2.getX(), p1.getY()-p2.getY(), p1.getZ()-p2.getZ());
	}

	Point3d operator+(const Point3d& p, const Vector3d& v)
	{
		return Point3d(p.getX()+v.getX(), p.getY()+v.getY(), p.getZ()+v.getZ());
	}

	std::ostream& operator<<(std::ostream& out, const Point3d& p)
	{
		out << "(" << p.getX() << ", " << p.getY() << ", " << p.getZ() << ")" << std::endl;

		return out;
	}
}}}