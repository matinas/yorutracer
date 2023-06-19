#ifndef VECTOR3D_H
#define VECTOR3D_H

namespace yoru {
namespace math {

	class Point3d;

	class Vector3d
	{
	public:
		Vector3d();
		Vector3d(float x, float y, float z);
		~Vector3d();

		float getX() const;
		float getY() const;
		float getZ() const;

		float norm();
		void normalize();

		friend float operator*(const Vector3d& v1, const Vector3d& v2);
		friend Vector3d operator+(const Vector3d& v1, const Vector3d& v2);
		friend Vector3d operator*(const Vector3d& v1, float f);
		friend Vector3d operator*(float f, const Vector3d& v1);
		friend float operator*(const Vector3d& v, const Point3d& p);
		friend bool operator==(const Vector3d& v1, const Vector3d& v2);

	private:
		float x, y, z;
		float xNorm, yNorm, zNorm;
	};
}}

#endif
