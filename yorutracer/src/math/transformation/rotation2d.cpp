#include <math.h>

#include "math\transformation\rotation2d.h"

namespace yoru {
namespace math {

	Rotation2d::Rotation2d()
	{
	}

	Rotation2d::Rotation2d(float degrees)
	{
		this->degrees = degrees;

		this->matrix = Matrix3x3(cos(degrees), -sin(degrees), 0.0,
								 sin(degrees), cos(degrees), 0.0,
								 0.0f, 0.0f, 1.0f);

		this->rotation = this;
		this->translation = nullptr;
		this->scale = nullptr;
	}

	Rotation2d::~Rotation2d()
	{
	}

	Affine2d Rotation2d::inverse()
	{
		return this->matrix.transpose(); // the inverse of a rotation matrix is the rotation matrix's transpose
	}
}}