#include <iostream>
#include <cstdlib>

#include "math\transformation\affine2d.h"
#include "math\transformation\rotation2d.h"
#include "math\transformation\translation2d.h"
#include "math\transformation\scale2d.h"
#include "math\matrix\matrixfactory.h"

namespace yoru {
namespace math {

	Affine2d::Affine2d()
	{
	}

	Affine2d::Affine2d(Matrix3x3* mat)
	{
		this->matrix = mat;
	}

	Affine2d::Affine2d(Rotation2d* rot, Translation2d* trans, Scale2d* scale)
	{
		initTransforms(rot, trans, scale);

		Matrix3x3 *rotM, *transM, *scaleM;
		fillMatrices(rotM, transM, scaleM);

		this->matrix = *((*rotM) * (*scaleM)) * (*transM);
	}

	Affine2d::Affine2d(Rotation2d* rot, Scale2d* scale, Translation2d* trans)
	{
		initTransforms(rot, trans, scale);

		Matrix3x3 *rotM, *transM, *scaleM;
		fillMatrices(rotM, transM, scaleM);

		this->matrix = *((*rotM) * (*transM)) * (*scaleM);
	}

	void Affine2d::initTransforms(Rotation2d* rot, Translation2d* trans, Scale2d* scale)
	{
		this->rotation = rot;
		this->translation = trans;
		this->scale = scale;
	}

	void Affine2d::fillMatrices(Matrix3x3*& rotM, Matrix3x3*& transM, Matrix3x3*& scaleM)
	{
		rotM = this->rotation ? this->rotation->getMatrix() : Matrix3x3::identity;
		transM = this->translation ? this->translation->getMatrix() : Matrix3x3::identity;
		scaleM = this->scale ?this->scale->getMatrix() : Matrix3x3::identity;
	}

	Affine2d::~Affine2d()
	{
		// if (rotation) delete rotation;
		// if (scale) delete scale;
		// if (translation) delete translation;
	}

	Affine2d Affine2d::inverse()
	{
		if (!(this->scale && this->rotation))
		{
			// we can assume that the transformation represents a composition of rotation OR scale, and translation transforms
			// so the inverse can be easily derived as described here (it's the same for 3x3): https://graphics.stanford.edu/courses/cs248-98-fall/Final/q4.html

			Vector3d translationVec = matrix->getCol(2);

			Vector3d row0 = Vector3d(matrix->getItem(0, 0), matrix->getItem(1, 0), -(matrix->getCol(0) * translationVec));
			Vector3d row1 = Vector3d(matrix->getItem(0, 1), matrix->getItem(1, 1), -(matrix->getCol(1) * translationVec));
			Vector3d row2 = Vector3d(0, 0, 1);

			return Affine2d(MatrixFactory::getMatrix(row0, row1, row2));
		}
		else // if the transformation involves both rotation and scale, the inverse calcualtion is a bit more complex (LU decomp, SVD, etc)
		{
			return Affine2d(this->matrix->inverse());
		}
	}

	Affine2d operator*(const Affine2d& t1, const Affine2d& t2)
	{
		return Affine2d((*t1.matrix) * (*t2.matrix));
	}

	Point2d operator*(const Affine2d& t, const Point2d& p)
	{
		return (*t.matrix) * p;
	}
}}
