#ifndef SCALE2D_H
#define SCALE2D_H

#include "math\transformation\affine2d.h"

namespace yoru {
namespace math {

	class Scale2d : public Affine2d
	{
	public:
		Scale2d();
		Scale2d(float sx, float sy);
		~Scale2d();

		virtual Affine2d inverse();

		friend Scale2d operator*(const Scale2d& s1, const Scale2d& s2);

	private:
		float sx, sy;
		bool mirrored;
	};
}}

#endif
