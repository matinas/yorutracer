#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

// deprecated
// use the more generic math::Vector<T,D>

namespace yoru {
namespace math {

	template <typename T, size_t D>
	class Vector;

namespace deprecated {

	class Point3d;

	class Vector3d
	{
	public:
		Vector3d();
		Vector3d(float x, float y, float z);
		
		// conversion constructor for backwards compatibility with the more generic Vector<T,D>
		// it allow to convert a Vector3f into a deprecated Vector3d so as to, for instance, be
		// able to properly convert the Vector3f resulting from the difference between two Point3f
		template <typename T>
		Vector3d(Vector<T,3> v)
		{
			this->x = v.getX();
			this->y = v.getY();
			this->z = v.getZ();
		}

		~Vector3d();

		float& operator[](unsigned index)
		{
			switch (index)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default:
				std::cout << "[Error] Can't retrieve coordinate for 3D vector, returning last available coordinate" << std::endl;
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

		float norm();
		void normalize();
		Vector3d cross(const Vector3d& v);
		float dot(const Vector3d& v);

		friend float operator*(const Vector3d& v1, const Vector3d& v2);
		friend Vector3d operator+(const Vector3d& v1, const Vector3d& v2);
		friend Vector3d operator*(const Vector3d& v1, float f);
		friend Vector3d operator*(float f, const Vector3d& v1);
		friend Vector3d operator-(const Vector3d& v);
		friend float operator*(const Vector3d& v, const Point3d& p);
		friend bool operator==(const Vector3d& v1, const Vector3d& v2);
		friend std::ostream& operator<<(std::ostream& out, const Vector3d& v);

	private:
		float x, y, z;
		float xNorm, yNorm, zNorm;
	};

	typedef Vector3d Vector3f; // we define this in this way so as to be able to refer to either this deprecated Vector3d or the newer more generic Vector<T,3>
							   // as Vector3f (one inside yoru::math and the other inside yoru::math::deprecated). switching between one or the other is just
							   // a matter of defining USE_DEPRECATED_VECTOR inside commons.h (which ends up setting the proper namespace alias yorumathvector)
}}}

#endif
