#include "math\matrix\matrix3x3.h"
#include "math\matrix\matrixfactory.h"

namespace yoru {
namespace math {

	Matrix3x3* const Matrix3x3::identity = MatrixFactory::getMatrix(1.0f, 0.0f, 0.0f,
																	0.0f, 1.0f, 0.0f,
																	0.0f, 0.0f, 1.0f);

	Matrix3x3* operator*(const Matrix3x3& mat1, const Matrix3x3& mat2)
	{
		yorumathvector::Vector3f mat1row0 = mat1.getRow(0); yorumathvector::Vector3f mat1row1 = mat1.getRow(1); yorumathvector::Vector3f mat1row2 = mat1.getRow(2);
		yorumathvector::Vector3f mat2col0 = mat2.getCol(0); yorumathvector::Vector3f mat2col1 = mat2.getCol(1); yorumathvector::Vector3f mat2col2 = mat2.getCol(2);

		yorumathvector::Vector3f row0 = yorumathvector::Vector3f(mat1row0*mat2col0, mat1row0*mat2col1, mat1row0*mat2col2);
		yorumathvector::Vector3f row1 = yorumathvector::Vector3f(mat1row1*mat2col0, mat1row1*mat2col1, mat1row1*mat2col2);
		yorumathvector::Vector3f row2 = yorumathvector::Vector3f(mat1row2*mat2col0, mat1row2*mat2col1, mat1row2*mat2col2);

		return MatrixFactory::getMatrix(row0, row1, row2);
	}

	Matrix3x3* operator+(const Matrix3x3& mat1, const Matrix3x3& mat2)
	{
		yorumathvector::Vector3f row0 = mat1.getRow(0) + mat2.getRow(0);
		yorumathvector::Vector3f row1 = mat1.getRow(1) + mat2.getRow(1);
		yorumathvector::Vector3f row2 = mat1.getRow(2) + mat2.getRow(2);

		return MatrixFactory::getMatrix(row0, row1, row2);
	}

	yorumathpoint::Point3f operator*(const Matrix3x3& mat, const yorumathpoint::Point3f& p)
	{
		// we are using a traditional column-vector convention, so
		// to post-multiply (M*p) we must take the rows of the matrix

		return yorumathpoint::Point3f(mat.getRow(0)*p, mat.getRow(1)*p, mat.getRow(2)*p);
	}

	yorumathpoint::Point2i operator*(const Matrix3x3& mat, const yorumathpoint::Point2i& p)
	{
		yorumathpoint::Point3f point = yorumathpoint::Point3f(static_cast<float>(p.getX()), static_cast<float>(p.getY()), 1.0f);
		yorumathpoint::Point3f prod = mat * point;

		return yorumathpoint::Point2i(static_cast<int>(prod.getX()), static_cast<int>(prod.getY()));
	}

	yorumathpoint::Point2f operator*(const Matrix3x3& mat, const yorumathpoint::Point2f& p)
	{
		yorumathpoint::Point3f point = yorumathpoint::Point3f(p.getX(), p.getY(), 1.0f);
		yorumathpoint::Point3f prod = mat * point;

		return yorumathpoint::Point2f(prod.getX(), prod.getY());
	}

	bool operator==(const Matrix3x3& mat1, const Matrix3x3& mat2)
	{
		return (mat1.getRow(0) == mat2.getRow(1))
			&& (mat1.getRow(1) == mat2.getRow(1))
			&& (mat1.getRow(2) == mat2.getRow(2));
	}
}}