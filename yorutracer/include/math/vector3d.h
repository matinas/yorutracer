#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "math\point3d.h"

namespace yoru {
namespace math {

	class Vector3d
	{
	public:
		Vector3d();
		Vector3d(float x, float y, float z);
		~Vector3d();

		float getX() const;
		float getY() const;
		float getZ() const;

		friend float operator*(Vector3d v1, Vector3d v2);
		friend Vector3d operator+(Vector3d v1, Vector3d v2);
		friend Vector3d operator*(Vector3d v1, float f);
		friend Vector3d operator*(float f, Vector3d v1);
		friend float operator*(Vector3d v, Point3d p);
		friend bool operator==(Vector3d v1, Vector3d v2);

	private:
		float x, y, z;
	};
}}

#endif
