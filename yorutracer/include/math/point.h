#ifndef POINT_H
#define POINT_H

#define POINT_DIMENSION_CONSTRUCTOR_FAIL "Trying to construct a point with an amount of parameters not matching dimension"
#define POINT_DIMENSION_GETCOORD_FAIL "Trying to get a coordinate which does not exist for the vector's dimension"

#include <iostream>

#include "utils\commons.h"
#include "math\deprecated\point3d.h" // for backwards compatibility with Point3d
#include "math\deprecated\point2d.h" // for backwards compatibility with Point2d<T>

// TODO: starting from C++11 we could implement these generic constructors in a much more easier and readable way either by using parameter packs or initializer_list
// TODO: create a test suite module for the Vector class

#ifdef USE_DEPRECATED_POINT
namespace yorumathpoint = yoru::math::deprecated; // define this to either yoru::math to use the generic Point<T,D> class or to yoru::math::deprecated to use the old Point3d and Point2d<T> classes
#else
namespace yorumathpoint = yoru::math;
#endif

namespace yoru {
namespace math {

	namespace deprecated 
	{
		class Vector3d;
	}

	template <typename T, size_t D>
	class Point;

	template <typename T, size_t D>
	class Vector;

	template <typename T, size_t D>
	bool operator==(const Point<T,D>& p1, const Point<T,D>& p2);

	template <typename T, size_t D>
	math::Vector<T,D> operator-(const Point<T,D>& p1, const Point<T,D>& p2);

	template <typename T, size_t D>
	Point<T,D> operator+(const Point<T,D>& p, const math::Vector<T,D>& v);

	template <typename T, size_t D>
	float operator*(const Point<T,D>& p, const math::Vector<T,D>& v);

	template <typename T, size_t D>
	std::ostream& operator<<(std::ostream& out, const Point<T,D>& v);

	template <typename T, size_t D>
	class Point
	{
	public:
		Point()
		{
			for (size_t i = 0; i < D; ++i)
				this->coords[i] = static_cast<T>(0);
		}

		// for backwards compatibility with the deprecated Vector3d
		Point(deprecated::Point3d& p)
		{
			static_assert(D == 3, POINT_DIMENSION_CONSTRUCTOR_FAIL);
			coords[0] = p.getX();
			coords[1] = p.getY();
			coords[2] = p.getZ();
		}

		// instead of these constructors with static_asserts we could've have create specializations
		// inheriting from Point and just implement each specific constructor on each specialization

		Point(T x)
		{
			static_assert(D == 1, POINT_DIMENSION_CONSTRUCTOR_FAIL);
			coords[0] = x;
		}

		Point(T x, T y)
		{
			static_assert(D == 2, POINT_DIMENSION_CONSTRUCTOR_FAIL);
			coords[0] = x;
			coords[1] = y;
		}

		Point(T x, T y, T z)
		{
			static_assert(D == 3, POINT_DIMENSION_CONSTRUCTOR_FAIL);
			coords[0] = x;
			coords[1] = y;
			coords[2] = z;
		}

		Point(T x, T y, T z, T w)
		{
			static_assert(D == 4, POINT_DIMENSION_CONSTRUCTOR_FAIL);
			coords[0] = x;
			coords[1] = y;
			coords[2] = z;
			coords[3] = w;
		}

		~Point() {}

		T& operator[](unsigned index)
		{
			return this->coords[index];
		}

		T operator[](unsigned index) const
		{
			return this->coords[index];
		}

		T getX() const
		{
			static_assert(D >= 1, POINT_DIMENSION_GETCOORD_FAIL);
			return this->coords[0];
		}

		T getY() const
		{
			static_assert(D >= 2, POINT_DIMENSION_GETCOORD_FAIL);
			return this->coords[1];
		}

		T getZ() const
		{
			static_assert(D >= 3, POINT_DIMENSION_GETCOORD_FAIL);
			return this->coords[2];
		}

		T getW() const
		{
			static_assert(D >= 4, POINT_DIMENSION_GETCOORD_FAIL);
			return this->coords[3];
		}

		float distanceTo(const Point& p)
		{
			return 0;
		}

		friend bool operator== <>(const Point<T,D>& p1, const Point<T,D>& p2);
		friend Vector<T,D> operator- <>(const Point<T,D>& p1, const Point<T,D>& p2);
		friend Point<T,D> operator+ <>(const Point<T,D>& p, const Vector<T,D>& v);
		friend std::ostream& operator<< <>(std::ostream& out, const Point<T,D>& v);

		// for backwards compatibility with the older and less generic math classes so as to
		// be able to mix them together (e.g.: add a generic Point3f to a old Vector3d)

		friend Point<T,3> operator+ <>(const Point<T,3>& p, const deprecated::Vector3d& v);
		friend Point<T,3> operator+ <>(const deprecated::Vector3d& v, const Point<T,3>& p);
		friend float operator* <>(const Point<T,3>& p, const deprecated::Vector3d& v);
		friend float operator* <>(const deprecated::Vector3d& v, const Point<T,3>& p);

	private:
		T coords[D];
	};

	typedef Point<float,2> Point2f;
	typedef Point<float,3> Point3f;
	typedef Point<float,4> Point4f;

	typedef Point<unsigned,2> Point2u;
	typedef Point<unsigned,3> Point3u;
	typedef Point<unsigned,4> Point4u;

	typedef Point<int,2> Point2i;
	typedef Point<int,3> Point3i;
	typedef Point<int,4> Point4i;

	//////////////
	// friend function templates for Point<T,D>

	template <typename T, size_t D>
	bool operator==(const Point<T,D>& p1, const Point<T,D>& p2)
	{
		bool equal = true;
		for (int i=0; i<D && equal; ++i)
		{
			equal = equal && (p1[i] == p2[i]);
		}

		return equal;
	}

	//////////////
	// friend function template specializations for Point<T,2>

	// TODO: we could turn these into a more generic function template operator<T,D> by properly iterating through the available coords

	template <typename T>
	math::Vector<T,2> operator-(const Point<T,2>& p1, const Point<T,2>& p2)
	{
		return Vector<T,2>(p1.getX()-p2.getX(), p1.getY()-p2.getY());
	}

	template <typename T>
	math::Point<T,2> operator+(const Point<T,2>& p, const Vector<T,2>& v)
	{
		return Point<T,2>(p.getX()+v.getX(), p.getY()+v.getY());
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& out, const Point<T,2>& p)
	{
		out << "(" << p.getX() << ", " << p.getY() << ")";

		return out;
	}

	//////////////
	// friend function template specializations for Point<T,3>

	// TODO: we could turn these into a more generic function template operator<T,D> by properly iterating through the available coords

	template <typename T>
	math::Vector<T,3> operator-(const Point<T,3>& p1, const Point<T,3>& p2)
	{
		return Vector<T,3>(p1.getX()-p2.getX(), p1.getY()-p2.getY(), p1.getZ()-p2.getZ());
	}

	template <typename T>
	math::Point<T,3> operator+(const Point<T,3>& p, const Vector<T,3>& v)
	{
		return Point<T,3>(p.getX()+v.getX(), p.getY()+v.getY(), p.getZ()+v.getZ());
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& out, const Point<T,3>& p)
	{
		out << "(" << p.getX() << ", " << p.getY() << ", " << p.getZ() << ")";

		return out;
	}

	//////////////
	// friend function templates for backwards compatibility

	template <typename T>
	Point<T,3> operator+ (const Point<T,3>& p, const deprecated::Vector3d& v)
	{
		return Point<T,3>(p.getX()+v.getX(), p.getY()+v.getY(), p.getZ()+v.getZ());
	}

	template <typename T>
	Point<T,3> operator+ (const deprecated::Vector3d& v, const Point<T,3>& p)
	{
		return p+v;
	}

	template <typename T>
	float operator* <>(const deprecated::Vector3d& v, const Point<T,3>& p)
	{
		return v.getX()*p.getX() + v.getY()*p.getY() + v.getZ()*p.getZ();
	}

	template <typename T>
	float operator* <>(const Point<T,3>& p, const deprecated::Vector3d& v)
	{
		return v*p;
	}

	#undef POINT_DIMENSION_CONSTRUCTOR_FAIL
	#undef POINT_DIMENSION_GETCOORD_FAIL
}}

#endif
