#include <cstdlib>

#include "math\transformation\transform2d.h"
#include "math\transformation\rotation2d.h"
#include "math\transformation\translation2d.h"
#include "math\transformation\scale2d.h"

namespace yoru {
namespace math {

	Transform2d::Transform2d()
	{
	}

	Transform2d::Transform2d(Matrix3x3* mat)
	{
		this->matrix = mat;
	}

	Transform2d::~Transform2d()
	{
	}

	Matrix3x3* Transform2d::getMatrix()
	{
		return this->matrix;
	}

	Transform2d Transform2d::inverse()
	{
		return Transform2d(this->matrix->inverse());
	}

	Transform2d operator*(const Transform2d& t1, const Transform2d& t2)
	{
		return Transform2d((*t1.matrix) * (*t2.matrix));
	}

	Point2d operator*(const Transform2d& t, const Point2d& p)
	{
		return (*t.matrix) * p;
	}
}}
