#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "yoru\math\point3d.h"

class Vector3d
{
public:
	Vector3d();
	Vector3d(float x, float y, float z);
	~Vector3d();

	float getX();
	float getY();
	float getZ();

	friend float operator*(Vector3d v1, Vector3d v2);
	friend Vector3d operator+(Vector3d v1, Vector3d v2);
	friend Vector3d operator*(Vector3d v1, float f);
	friend Vector3d operator*(float f, Vector3d v1);
	friend float operator*(Vector3d v, Point3d p);

private:
	float x, y, z;
};

#endif
