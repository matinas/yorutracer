#include "math\matrix3x3.h"

namespace yoru {
namespace math {

	const Matrix3x3 Matrix3x3::identity = Matrix3x3(1.0f, 0.0f, 0.0f,
													0.0f, 1.0f, 0.0f,
													0.0f, 0.0f, 1.0f);
	Matrix3x3::Matrix3x3()
	{
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
			{
				items[i][j] = 0.0f;
			}
	}

	Matrix3x3::Matrix3x3(float item00, float item01, float item02,
						 float item10, float item11, float item12,
						 float item20, float item21, float item22)
	{
		this->items[0][0] = item00; this->items[0][1] = item01; this->items[0][2] = item02;
		this->items[1][0] = item10; this->items[1][1] = item11; this->items[1][2] = item12;
		this->items[2][0] = item20; this->items[2][1] = item21; this->items[2][2] = item22;
	}

	Matrix3x3::Matrix3x3(Vector3d row0, Vector3d row1, Vector3d row2)
	{
		this->items[0][0] = row0.getX(); this->items[0][1] = row0.getY(); this->items[0][2] = row0.getZ();
		this->items[1][0] = row1.getX(); this->items[1][1] = row1.getY(); this->items[1][2] = row1.getZ();
		this->items[2][0] = row2.getX(); this->items[2][1] = row2.getY(); this->items[2][2] = row2.getZ();
	}

	Matrix3x3::Matrix3x3(float items[3][3])
	{
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				this->items[i][j] = items[i][j];
	}

	Matrix3x3::~Matrix3x3()
	{
	}

	float Matrix3x3::getItem(int i, int j) const
	{
		return items[i][j];
	}

	Vector3d Matrix3x3::getRow(int row) const
	{
		return Vector3d(items[row][0], items[row][1], items[row][2]);
	}

	Vector3d Matrix3x3::getCol(int col) const
	{
		return Vector3d(items[0][col], items[1][col], items[2][col]);
	}

	int Matrix3x3::det()
	{
		// TODO: follow the traditional method for computing the determinant of a 3x3 matrix: https://www.wikihow.com/Find-the-Determinant-of-a-3X3-Matrix

		return 0;
	}

	Matrix3x3 Matrix3x3::inverse()
	{
		// TODO: follow the traditional method for computing the inverse of a 3x3 matrix: https://www.wikihow.com/Find-the-Inverse-of-a-3x3-Matrix
		// here's a ready-to-use implementation for 4x4 matrices: https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix (MESA / glm implementation)
		// we could also use any of the standard decomposition methods (LU, QR, SCV, Cholesky, etc)

		Matrix3x3 matT = this->transpose();

		return identity;
	}

	Matrix3x3 Matrix3x3::transpose()
	{
		return Matrix3x3(getCol(0), getCol(1), getCol(2));
	}

	Matrix3x3 operator*(const Matrix3x3& mat1, const Matrix3x3& mat2)
	{
		Vector3d row0 = Vector3d(mat1.getRow(0)*mat2.getCol(0), mat1.getRow(0)*mat2.getCol(1), mat1.getRow(0)*mat2.getCol(2));
		Vector3d row1 = Vector3d(mat1.getRow(1)*mat2.getCol(0), mat1.getRow(1)*mat2.getCol(1), mat1.getRow(1)*mat2.getCol(2));
		Vector3d row2 = Vector3d(mat1.getRow(2)*mat2.getCol(0), mat1.getRow(2)*mat2.getCol(1), mat1.getRow(2)*mat2.getCol(2));

		return Matrix3x3(row0, row1, row2);
	}

	Matrix3x3 operator+(const Matrix3x3& mat1, const Matrix3x3& mat2)
	{
		Vector3d row0 = mat1.getRow(0) + mat2.getRow(0);
		Vector3d row1 = mat1.getRow(1) + mat2.getRow(1);
		Vector3d row2 = mat1.getRow(2) + mat2.getRow(2);

		return Matrix3x3(row0, row1, row2);
	}

	Point3d operator*(const Matrix3x3& mat, const Point3d& p)
	{
		return Point3d(mat.getRow(0)*p, mat.getRow(1)*p, mat.getRow(2)*p);
	}

	Point2d operator*(const Matrix3x3& mat, const Point2d& p)
	{
		Point3d point = Point3d(static_cast<float>(p.getX()), static_cast<float>(p.getY()), 1.0f);
		Point3d prod = mat*point;

		return Point2d(prod.getX(), prod.getY());
	}
}}