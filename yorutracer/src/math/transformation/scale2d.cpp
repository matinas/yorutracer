#include "math\transformation\scale2d.h"
#include "math\matrix\matrixfactory.h"

namespace yoru {
namespace math {

	Scale2d::Scale2d()
	{
	}

	Scale2d::Scale2d(float sx, float sy)
	{
		this->sx = sx;
		this->sy = sy;
		
		this->matrix = MatrixFactory::getMatrix(sx, 0.0f, 0.0f,
												0.0f, sy, 0.0f,
												0.0f, 0.0f, 1.0f);
		this->scale = this;
		this->translation = nullptr;
		this->rotation = nullptr;
	}

	Scale2d::~Scale2d()
	{
	}

	Affine2d Scale2d::inverse()
	{
		return Scale2d(1.0f/sx, 1.0f/sy); // the inverse of a scale matrix is the scale matrix with
										  // the inverted scale factors on each of the scale components
	}

	Scale2d operator*(const Scale2d& s1, const Scale2d& s2)
	{
		return Scale2d(s1.sx*s2.sx, s1.sy*s2.sy);
	}
}}
