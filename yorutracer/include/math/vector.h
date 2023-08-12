#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

#include "utils\common.h"
#include "math\deprecated\vector3d.h"

// all these macros are used to generate and embbed a sort of "variadic constructor" (i.e.: a constructor that can take any number of parameters) into the Vector class
// so as to comply with the C++0x standard (one of the alternatives pre-C++11, as C++11 introduced parameter packs and variadic templates which makes it much easier)
// in short, the generic constructor is implemented using macro-based metaprogramming (ala Boost library)

// TODO: starting from C++11 we could implement these generic constructors in a much more easier and readable way either by using parameter packs or initializer_list
// TODO: create a test suite module for the Vector class

//#define USE_CUSTOM_COPY_CONSTRUCTOR

#define VECTOR_COORD(n) VECTOR_COORD_ ## n // ## is used to append something to an identifier and generate a new preprocessor identifier out of it
#define VECTOR_GENERATE_COORD_PARAMS(n) VECTOR_GENERATE_COORD_PARAMS_ ## n
#define VECTOR_GENERATE_COORD_ARGS(n) VECTOR_GENERATE_COORD_ARGS_ ## n
#define VECTOR_DIMENSION_ASSERT(n,d) VECTOR_DIMENSION_ASSERT_ ## n(d)

#define VECTOR_COORD_1 x
#define VECTOR_COORD_2 y
#define VECTOR_COORD_3 z
#define VECTOR_COORD_4 w

#define VECTOR_GENERATE_COORD_ARGS_1 VECTOR_COORD(1)
#define VECTOR_GENERATE_COORD_ARGS_2 VECTOR_COORD(1), VECTOR_COORD(2)
#define VECTOR_GENERATE_COORD_ARGS_3 VECTOR_COORD(1), VECTOR_COORD(2), VECTOR_COORD(3)
#define VECTOR_GENERATE_COORD_ARGS_4 VECTOR_COORD(1), VECTOR_COORD(2), VECTOR_COORD(3), VECTOR_COORD(4)

#define VECTOR_GENERATE_COORD_PARAMS_1 const T& VECTOR_COORD(1)
#define VECTOR_GENERATE_COORD_PARAMS_2 const T& VECTOR_COORD(1), const T& VECTOR_COORD(2)
#define VECTOR_GENERATE_COORD_PARAMS_3 const T& VECTOR_COORD(1), const T& VECTOR_COORD(2), const T& VECTOR_COORD(3)
#define VECTOR_GENERATE_COORD_PARAMS_4 const T& VECTOR_COORD(1), const T& VECTOR_COORD(2), const T& VECTOR_COORD(3), const T& VECTOR_COORD(4)

#define VECTOR_DIMENSION_CONSTRUCTOR_FAIL "Trying to construct a vector with an amount of parameters not matching dimension"
#define VECTOR_DIMENSION_GETCOORD_FAIL "Trying to get a coordinate which does not exist for the vector's dimension"

#define VECTOR_DIMENSION_ASSERT_1(d) static_assert(d == 1, VECTOR_DIMENSION_CONSTRUCTOR_FAIL);
#define VECTOR_DIMENSION_ASSERT_2(d) static_assert(d == 2, VECTOR_DIMENSION_CONSTRUCTOR_FAIL);
#define VECTOR_DIMENSION_ASSERT_3(d) static_assert(d == 3, VECTOR_DIMENSION_CONSTRUCTOR_FAIL);
#define VECTOR_DIMENSION_ASSERT_4(d) static_assert(d == 4, VECTOR_DIMENSION_CONSTRUCTOR_FAIL);

// this macro contains the "template" logic for the set of constructors with varying parameters
#define VECTOR_CONSTRUCTOR_FACTORY(n,T,D) \
Vector(VECTOR_GENERATE_COORD_PARAMS(n)) \
{ \
	VECTOR_DIMENSION_ASSERT(n, D) \
	T arr[] = { VECTOR_GENERATE_COORD_ARGS(n) }; \
	for (size_t i = 0; i < n; ++i) \
		coords[i] = arr[i]; \
}

#define VECTOR_CONSTRUCTOR_FOREACH_ARGNUM(m,T,D) m(1,T,D) m(2,T,D) m(3,T,D) m(4,T,D)

#ifdef USE_DEPRECATED_VECTOR
namespace yorumathvector = yoru::math::deprecated; // define this to either yoru::math to use the generic Vector<T,D> class or to yoru::math::deprecated to use the old Vector3d and Vector2d classes
#else
namespace yorumathvector = yoru::math; // define this to either yoru::math to use the generic Vector<T,D> class or to yoru::math::deprecated to use the old Vector3d and Vector2d classes
#endif

namespace yoru {
namespace math {

	//////////////
	// Templates forward declarations

	template <typename T, size_t D>
	class Vector;

	template <typename T, size_t D>
	class Point;

	template <typename T, size_t D>
	float operator*(const Vector<T,D>& v1, const Vector<T,D>& v2);
	
	template <typename T, size_t D>
	Vector<T,D> operator+(const Vector<T,D>& v1, const Vector<T,D>& v2);

	template <typename T, size_t D>
	Vector<T,D> operator*(const Vector<T,D>& v1, float f);

	template <typename T, size_t D>
	Vector<T,D> operator*(float f, const Vector<T,D>& v1);

	template <typename T, size_t D>
	Vector<T,D> operator-(const Vector<T,D>& v);

	template <typename T, size_t D>
	float operator*(const Vector<T,D>& v, const Point<T,D>& p);

	template <typename T, size_t D>
	bool operator==(const Vector<T,D>& v1, const Vector<T,D>& v2);

	template <typename T, size_t D>
	std::ostream& operator<<(std::ostream& out, const Vector<T,D>& v);

	template <typename T, size_t D>
	class Vector
	{
	public:
		Vector()
		{
			for (size_t i = 0; i < D; ++i)
				this->coords[i] = static_cast<T>(0);
		}

		// for backwards compatibility with the deprecated Vector3d
		Vector(const deprecated::Vector3d& v)
		{
			static_assert(D == 3, VECTOR_DIMENSION_GETCOORD_FAIL);
			this->coords[0] = v.getX();
			this->coords[1] = v.getY();
			this->coords[2] = v.getZ();
		}

		Vector(const T coords[D])
		{
			memcpy(this->coords, coords, D*sizeof(T));
		}

		// copy constructor
		// note that including the custom copy constructor is slightly less efficient vs. the default one (apparently more efficient) generated by the compiler
#ifndef USE_CUSTOM_COPY_CONSTRUCTOR
		// Vector(const Point<T, D> &p) = default; // this works only for C++11 and up (explicitly defaulted functions support), but we could just remove the whole copy constructor for older versions
#else
		Vector(const Vector<T, D> &p) 
		{
			memcpy(this->coords, p.coords, D * sizeof(T));
		}
#endif

		// generates multiple versions of a Vector constructor with different number of parameters that
		// matches the specified dimension (akin a variadic function/constructor from C++11 and up)
		VECTOR_CONSTRUCTOR_FOREACH_ARGNUM(VECTOR_CONSTRUCTOR_FACTORY, T, D)

		~Vector() {}

		const T& getX() const
		{
			static_assert(D >= 1, VECTOR_DIMENSION_GETCOORD_FAIL);
			return this->coords[0];
		}

		const T& getY() const
		{
			static_assert(D >= 2, VECTOR_DIMENSION_GETCOORD_FAIL);
			return this->coords[1];
		}

		const T& getZ() const
		{
			static_assert(D >= 3, VECTOR_DIMENSION_GETCOORD_FAIL);
			return this->coords[2];
		}

		const T& getW() const
		{
			static_assert(D >= 4, VECTOR_DIMENSION_GETCOORD_FAIL);
			return this->coords[3];
		}

		float norm()
		{
			float normSqr = 0.0f;
			for (size_t i = 0; i < D; ++i)
				normSqr += this->coords[i] * this->coords[i];

			return sqrt(normSqr);
		}

		void normalize()
		{
			float coef = 1/norm();
			for (size_t i = 0; i < D; ++i)
				this->coords[i] *= coef;
		}

		float dot(const Vector<T,D>& v)
		{
			return *this * v;
		}

		Vector cross(const Vector<T,2>& v)
		{
			return Vector<T,2>(this->getX()*v.getY() - this->getY()*v.getX());
		}

		Vector cross(const Vector<T,3>& v)
		{
			return Vector<T,3>(this->getY()*v.getZ() - this->getZ()*v.getY(),
							   this->getZ()*v.getX() - this->getX()*v.getZ(),
							   this->getX()*v.getY() - this->getY()*v.getX());
		}

		T& operator[](unsigned index)
		{
			return this->coords[index];
		}

		T operator[](unsigned index) const
		{
			return this->coords[index];
		}

		Vector& operator+=(const Vector& v);
		Vector& operator+=(const T& val);

		friend Vector operator* <>(float f, const Vector& v1);
		friend Vector operator- <>(const Vector& v);
		friend bool operator== <>(const Vector& v1, const Vector& v2);
		friend std::ostream& operator<< <>(std::ostream& out, const Vector& v);

		friend float operator* <>(const Vector<T,D>& v1, const Vector<T,D>& v2);
		friend Vector<T,D> operator+ <>(const Vector<T,D>& v1, const Vector<T,D>& v2);
		friend Vector operator* <>(const Vector& v1, float f);
		friend float operator* <>(const Vector& v, const Point<T,D>& p);

	private:
		T coords[D];
	};

	typedef Vector<float,2> Vector2f;
	typedef Vector<float,3> Vector3f;
	typedef Vector<float,4> Vector4f;

	typedef Vector<unsigned,2> Vector2u;
	typedef Vector<unsigned,3> Vector3u;
	typedef Vector<unsigned,4> Vector4u;

	typedef Vector<int,2> Vector2i;
	typedef Vector<int,3> Vector3i;
	typedef Vector<int,4> Vector4i;

	//////////////
	// function template definitions for Vector<T,D>

	template <typename T, size_t D>
	Vector<T,D>& Vector<T,D>::operator+=(const Vector<T,D>& v)
	{
		for (int i = 0; i < D; i++)
			this->coords[i] += v[i];

		return *this;
	}

	template <typename T, size_t D>
	Vector<T,D>& Vector<T,D>::operator+=(const T& val)
	{
		for (int i = 0; i < D; i++)
			this->coords[i] += val;

		return *this;
	}

	//////////////
	// friend function template definitions for Vector<T,D>
	
	template <typename T, size_t D>
	Vector<T,D> operator*(float f, const Vector<T,D>& v1)
	{
		return v1*f;
	}

	template <typename T, size_t D>
	Vector<T,D> operator-(const Vector<T,D>& v)
	{
		return Vector<T,D>(-v.getX(), -v.getY(), -v.getZ());
	}

	template <typename T, size_t D>
	bool operator==(const Vector<T,D>& v1, const Vector<T,D>& v2)
	{
		bool equal = true;
		for (int i=0; i<D && equal; ++i)
		{
			equal = equal && (v1[i] == v2[i]);
		}

		return equal;
	}

	template <typename T, size_t D>
	std::ostream& operator<<(std::ostream& out, const Vector<T, D>& v)
	{
		out << "(";
		for (int i = 0; i < D; i++)
		{
			out << v.coords[i];
			if (i != D-1) out << ",";
		}
		out << ")";

		return out;
	}

	//////////////
	// friend function template specializations for Vector<T,2>

	template <typename T>
	class Point2d;

	template <typename T>
	float operator*(const Vector<T,2>& v1, const Vector<T,2>& v2)
	{
		return v1.getX()*v2.getX() + v1.getY()*v2.getY();
	}

	template <typename T>
	Vector<T,2> operator+(const Vector<T,2>& v1, const Vector<T,2>& v2)
	{
		return Vector<T,2>(v1.getX() + v2.getX(), v1.getY() + v2.getY());
	}

	template <typename T>
	Vector<T,2> operator*(const Vector<T,2>& v1, float f)
	{
		return Vector<T,2>(v1.getX()*f, v1.getY()*f);
	}

	template <typename T>
	float operator*(const Vector<T,2>& v, const Point2d<T>& p)
	{
		return v.getX()*p.getX() + v.getY()*p.getY();
	}

	//////////////
	// friend function template specializations for Vector<T,3>

	template <typename T>
	class Point3d;

	template <typename T>
	float operator*(const Vector<T,3>& v1, const Vector<T,3>& v2)
	{
		return v1.getX()*v2.getX() + v1.getY()*v2.getY() + v1.getZ()*v2.getZ();
	}

	template <typename T>
	Vector<T,3> operator+(const Vector<T,3>& v1, const Vector<T,3>& v2)
	{
		return Vector<T,3>(v1.getX() + v2.getX(), v1.getY() + v2.getY(), v1.getZ() + v2.getZ());
	}

	template <typename T>
	Vector<T,3> operator*(const Vector<T,3>& v1, float f)
	{
		return Vector<T,3>(v1.getX()*f, v1.getY()*f, v1.getZ()*f);
	}

	template <typename T>
	float operator*(const Vector<T,3>& v, const Point3d<T>& p)
	{
		return v.getX()*p.getX() + v.getY()*p.getY() + v.getZ()*p.getZ();
	}

	#undef USE_CUSTOM_COPY_CONSTRUCTOR
	#undef VECTOR_COORD
	#undef VECTOR_GENERATE_COORD_PARAMS
	#undef VECTOR_GENERATE_COORD_ARGS
	#undef VECTOR_DIMENSION_ASSERT
}}

#endif
