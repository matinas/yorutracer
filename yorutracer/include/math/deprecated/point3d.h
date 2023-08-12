#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>

// deprecated
// use the more generic math::Point<T,D>

namespace yoru {
namespace math {

	template <typename T, size_t D>
	class Point;

namespace deprecated {

	class Vector3d;

	class Point3d
	{
	public:
		Point3d();
		Point3d(float x, float y, float z);
		Point3d(const Point3d& p);

		// conversion constructor for backwards compatibility with the more generic Point<T,D>
		template <typename T>
		Point3d(Point<T,3> p)
		{
			this->x = p.getX();
			this->y = p.getY();
			this->z = p.getZ();
		}

		~Point3d();

		float& operator[](unsigned index)
		{
			switch (index)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default:
				std::cout << "[Error] Can't retrieve coordinate for 3D point, returning last available coordinate" << std::endl;
				return z;
			}
		}

		float operator[](unsigned index) const
		{
			return (*this)[index];
		}

		inline float getX() const;
		inline float getY() const;
		inline float getZ() const;

		float distanceTo(const Point3d& p);

		friend bool operator==(const Point3d& p1, const Point3d& p2);
		friend Vector3d operator-(const Point3d& p1, const Point3d& p2);
		friend Point3d operator+(const Point3d& p, const Vector3d& v);
		friend std::ostream& operator<<(std::ostream& out, const Point3d& v);

	private:
		float x, y, z;
	};

	typedef Point3d Point3f; // we define this in this way so as to be able to refer to either this deprecated Point3d or the newer more generic Point<T,3>
							 // as Point3f (one inside yoru::math and the other inside yoru::math::deprecated). switching between one or the other is just
							 // a matter of defining USE_DEPRECATED_POINT inside common.h (which ends up setting the proper namespace alias yorumathpoint)
}}}

#endif
