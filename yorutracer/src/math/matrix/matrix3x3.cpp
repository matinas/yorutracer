#include "math\matrix\matrix3x3.h"
#include "math\matrix\matrixfactory.h"

namespace yoru {
namespace math {

	Matrix3x3* const Matrix3x3::identity = MatrixFactory::getMatrix(1.0f, 0.0f, 0.0f,
																	0.0f, 1.0f, 0.0f,
																	0.0f, 0.0f, 1.0f);

	Matrix3x3* operator*(const Matrix3x3& mat1, const Matrix3x3& mat2)
	{
		Vector3d row0 = Vector3d(mat1.getRow(0)*mat2.getCol(0), mat1.getRow(0)*mat2.getCol(1), mat1.getRow(0)*mat2.getCol(2));
		Vector3d row1 = Vector3d(mat1.getRow(1)*mat2.getCol(0), mat1.getRow(1)*mat2.getCol(1), mat1.getRow(1)*mat2.getCol(2));
		Vector3d row2 = Vector3d(mat1.getRow(2)*mat2.getCol(0), mat1.getRow(2)*mat2.getCol(1), mat1.getRow(2)*mat2.getCol(2));

		return MatrixFactory::getMatrix(row0, row1, row2);
	}

	Matrix3x3* operator+(const Matrix3x3& mat1, const Matrix3x3& mat2)
	{
		Vector3d row0 = mat1.getRow(0) + mat2.getRow(0);
		Vector3d row1 = mat1.getRow(1) + mat2.getRow(1);
		Vector3d row2 = mat1.getRow(2) + mat2.getRow(2);

		return MatrixFactory::getMatrix(row0, row1, row2);
	}

	Point3d operator*(const Matrix3x3& mat, const Point3d& p)
	{
		// we are using a traditional column-vector convention, so
		// to post-multiply (M*p) we must take the rows of the matrix

		return Point3d(mat.getRow(0)*p, mat.getRow(1)*p, mat.getRow(2)*p);
	}

	Point2d<int> operator*(const Matrix3x3& mat, const Point2d<int>& p)
	{
		Point3d point = Point3d(static_cast<float>(p.getX()), static_cast<float>(p.getY()), 1.0f);
		Point3d prod = mat * point;

		return Point2d<int>(static_cast<int>(prod.getX()), static_cast<int>(prod.getY()));
	}

	Point2d<float> operator*(const Matrix3x3& mat, const Point2d<float>& p)
	{
		Point3d point = Point3d(static_cast<float>(p.getX()), static_cast<float>(p.getY()), 1.0f);
		Point3d prod = mat * point;

		return Point2d<float>(prod.getX(), prod.getY());
	}

	bool operator==(const Matrix3x3& mat1, const Matrix3x3& mat2)
	{
		return (mat1.getRow(0) == mat2.getRow(1))
			&& (mat1.getRow(1) == mat2.getRow(1))
			&& (mat1.getRow(2) == mat2.getRow(2));
	}
}}