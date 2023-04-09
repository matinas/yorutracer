#include "yoru\math\point3d.h"

Point3d::Point3d()
{
	this->x = 0;
	this->y = 0;
}

Point3d::Point3d(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Point3d::~Point3d()
{

}

int Point3d::getX()
{
	return x;
}

int Point3d::getY()
{
	return y;
}

int Point3d::getZ()
{
	return z;
}