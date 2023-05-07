#ifndef POINT3D_H
#define POINT3D_H

namespace yoru {
namespace math {

	class Point3d
	{
	public:
		Point3d();
		Point3d(float x, float y, float z);
		~Point3d();

		float getX() const;
		float getY() const;
		float getZ() const;

	private:
		float x, y, z;
	};
}}

#endif
