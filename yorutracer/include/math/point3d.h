#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>

namespace yoru {
namespace math {

	class Vector3d;

	class Point3d
	{
	public:
		Point3d();
		Point3d(float x, float y, float z);
		Point3d(const Point3d& p);
		~Point3d();

		float getX() const;
		float getY() const;
		float getZ() const;

		float distanceTo(const Point3d& p);

		friend bool operator==(const Point3d& p1, const Point3d& p2);
		friend Vector3d operator-(const Point3d& p1, const Point3d& p2);
		friend Point3d operator+(const Point3d& p, const Vector3d& v);
		friend std::ostream & operator<<(std::ostream& out, const Point3d& v);

	private:
		float x, y, z;
	};
}}

#endif
