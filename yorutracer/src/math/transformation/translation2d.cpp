#include "math\transformation\translation2d.h"
#include "math\matrix\matrixfactory.h"

namespace yoru {
namespace math {

	Translation2d::Translation2d()
	{
	}

	Translation2d::Translation2d(float tx, float ty)
	{
		this->tx = tx;
		this->ty = ty;

		this->matrix = MatrixFactory::getMatrix(1.0f, 0.0f, tx,
												0.0f, 1.0f, ty,
												0.0f, 0.0f, 1.0f);
		this->translation = this;
		this->scale = nullptr;
		this->rotation = nullptr;
	}

	Translation2d::~Translation2d()
	{
	}
	
	Affine2d Translation2d::inverse()
	{
		return Translation2d(-tx,-ty); // the inverse of a translation matrix is the translation matrix
									   // with the opposite signs on each of the translation components
	}
}}
