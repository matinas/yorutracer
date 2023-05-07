#ifndef ROTATION2D_H
#define ROTATION2D_H

#include "math\transformation\affine2d.h"

namespace yoru {
namespace math {

	class Rotation2d : public Affine2d
	{
	public:
		Rotation2d();
		Rotation2d(float degrees);
		~Rotation2d();

		virtual Affine2d inverse();

	private:
		float degrees;
	};
}}

#endif
