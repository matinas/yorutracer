#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H

#include "math\matrix\matrix3x3.h"

namespace yoru {
namespace math {

	class Transform2d
	{
	public:
		Transform2d();
		Transform2d(Matrix3x3* mat);
		~Transform2d();

		Matrix3x3* getMatrix();

		Transform2d inverse();

		friend Transform2d operator*(const Transform2d& t1, const Transform2d& t2);
		friend yorumathpoint::Point3f operator*(const Transform2d& t, const yorumathpoint::Point3f& p);
		friend yorumathpoint::Point2i operator*(const Transform2d& t, const yorumathpoint::Point2i& p);
		friend yorumathpoint::Point2f operator*(const Transform2d& t, const yorumathpoint::Point2f& p);

	protected:
		Matrix3x3* matrix;
	};
}}

#endif
