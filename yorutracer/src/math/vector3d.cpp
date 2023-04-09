#include "yoru\math\vector3d.h"

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

float Vector3d::getX()
{
	return x;
}

float Vector3d::getY()
{
	return y;
}

float Vector3d::getZ()
{
	return z;
}

float operator*(Vector3d v1, Vector3d v2)
{
	return v1.getX()*v2.getX() + v1.getY()*v2.getY() + v1.getZ()*v2.getZ();
}

Vector3d operator+(Vector3d v1, Vector3d v2)
{
	return Vector3d(v1.getX()+v2.getX(), v1.getY()+v2.getY(), v1.getZ()+v2.getZ());
}

Vector3d operator*(Vector3d v1, float f)
{
	return Vector3d(v1.getX()*f, v1.getY()*f, v1.getZ()*f);
}

Vector3d operator*(float f, Vector3d v1)
{
	return v1*f;
}

float operator*(Vector3d v, Point3d p)
{
	return v.getX()*p.getX() + v.getY()*p.getY() + v.getZ()*p.getZ();
}