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
		friend Point2d<int> operator*(const Transform2d& t, const Point2d<int>& p);
		friend Point2d<float> operator*(const Transform2d& t, const Point2d<float>& p);

	protected:
		Matrix3x3* matrix;
	};
}}

#endif
