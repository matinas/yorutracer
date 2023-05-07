#ifndef TRANSLATION2D_H
#define TRANSLATION2D_H

#include "math\transformation\transform2d.h"
#include "math\transformation\affine2d.h"

namespace yoru {
namespace math {

	class Translation2d : public Affine2d
	{
	public:
		Translation2d();
		Translation2d(float tx, float ty);
		~Translation2d();

		virtual Affine2d inverse();

	private:
		float tx, ty;
	};
}}

#endif
