#ifndef AFFINE2D_H
#define AFFINE2D_H

#include "math\transformation\transform2d.h"

namespace yoru {
namespace math {

	class Rotation2d;
	class Translation2d;
	class Scale2d;

	class Affine2d : public Transform2d
	{
	public:
		Affine2d();
		Affine2d(Matrix3x3* mat);
		Affine2d(Rotation2d* rot, Translation2d* trans, Scale2d* scale);
		Affine2d(Rotation2d* rot, Scale2d* scale, Translation2d* trans);
		Affine2d(Translation2d* trans, Scale2d* scale);
		Affine2d(Scale2d* scale, Translation2d* trans);
		~Affine2d();

		virtual Affine2d inverse();

		friend Affine2d operator*(const Affine2d& t1, const Affine2d& t2);
		friend Point2d<int> operator*(const Affine2d& t, const Point2d<int>& p);

	protected:
		Rotation2d* rotation;
		Translation2d* translation;
		Scale2d* scale;

	private:
		void initTransforms(Rotation2d* rot, Translation2d* trans, Scale2d* scale);
		void fillMatrices(Matrix3x3*& rotM, Matrix3x3*& transM, Matrix3x3*& scaleM);
	};
}}

#endif
