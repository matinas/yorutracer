#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include "math\point2d.h"
#include "math\point3d.h"
#include "math\vector3d.h"

namespace yoru {
namespace math
{
	class Matrix3x3
	{
	public:
		Matrix3x3();
		Matrix3x3(float item00, float item01, float item02, float item10, float item11, float item12, float item20, float item21, float item22);
		Matrix3x3(Vector3d row0, Vector3d row1, Vector3d row2);
		Matrix3x3(float mat[3][3]);
		~Matrix3x3();

		float getItem(int i, int j) const;
		Vector3d getRow(int row) const;
		Vector3d getCol(int col) const;

		int det();
		Matrix3x3 transpose();
		Matrix3x3 inverse();

		static const Matrix3x3 identity;

		friend Matrix3x3 operator*(const Matrix3x3& mat1, const Matrix3x3& mat2);
		friend Matrix3x3 operator+(const Matrix3x3& mat1, const Matrix3x3& mat2);
		friend Point3d operator*(const Matrix3x3& mat, const Point3d& p);
		friend Point2d operator*(const Matrix3x3& mat, const Point2d& p);

	private:
		float items[3][3];
	};
}}

#endif
