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

		// FIXME: this is not very performant, as we are multiplying by identity in vane when a specific transform is null as part of the constructor
	    // Don't use this for now... it will be probably removed later and define specific constructor for each combination of transforms
		this->matrix = *((*rotM) * (*scaleM)) * (*transM); 
	}

	Affine2d::Affine2d(Rotation2d* rot, Scale2d* scale, Translation2d* trans)
	{
		initTransforms(rot, trans, scale);

		Matrix3x3 *rotM, *transM, *scaleM;
		fillMatrices(rotM, transM, scaleM);

		// FIXME: take into account the same as above
		this->matrix = *((*rotM) * (*transM)) * (*scaleM);
	}

	Affine2d::Affine2d(Scale2d* scale, Translation2d* trans)
	{
		initTransforms(nullptr, trans, scale);

		this->matrix = *this->translation->getMatrix() * *this->scale->getMatrix();
	}

	Affine2d::Affine2d(Translation2d* trans, Scale2d* scale)
	{
		initTransforms(nullptr, trans, scale);

		this->matrix = *this->scale->getMatrix() * *this->translation->getMatrix();
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
		// FIXME: not working for some reason...

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

			yorumathvector::Vector3f translationVec = matrix->getCol(2);

			yorumathvector::Vector3f row0 = yorumathvector::Vector3f(matrix->getItem(0, 0), matrix->getItem(1, 0), -(matrix->getCol(0) * translationVec));
			yorumathvector::Vector3f row1 = yorumathvector::Vector3f(matrix->getItem(0, 1), matrix->getItem(1, 1), -(matrix->getCol(1) * translationVec));
			yorumathvector::Vector3f row2 = yorumathvector::Vector3f(0.f, 0.f, 1.f);

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

	yorumathpoint::Point2i operator*(const Affine2d& t, const yorumathpoint::Point2i& p)
	{
		return (*t.matrix) * p;
	}
}}
