#ifndef POINT3D_H
#define POINT3D_H

class Point3d
{
public:
	Point3d();
	Point3d(int x, int y, int z);
	~Point3d();

	int getX();
	int getY();
	int getZ();

private:
	int x, y, z;
};

#endif
