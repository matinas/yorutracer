#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include "math\point.h"
#include "math\deprecated\point2d.h"
#include "math\vector.h"

namespace yoru {
namespace math
{
	// represents a 3x3 matrix used by the Yoru engine
	// internally a matrix can be either a Yorumatrix (custom matrix), or a GLMMatrix (matrix implemented through glm library)

	class Matrix3x3
	{
	public:
		virtual float getItem(int i, int j) const = 0;
		virtual yorumathvector::Vector3f getRow(int row) const = 0;
		virtual yorumathvector::Vector3f getCol(int col) const = 0;

		~Matrix3x3() { delete identity; }

		virtual float det() = 0;
		virtual Matrix3x3* transpose() = 0;
		virtual Matrix3x3* inverse() = 0;

		friend Matrix3x3* operator*(const Matrix3x3& mat1, const Matrix3x3& mat2);
		friend Matrix3x3* operator+(const Matrix3x3& mat1, const Matrix3x3& mat2);
		friend yorumathpoint::Point3f operator*(const Matrix3x3& mat, const yorumathpoint::Point3f& p);
		friend yorumathpoint::Point2i operator*(const Matrix3x3& mat, const yorumathpoint::Point2i& p);
		friend yorumathpoint::Point2f operator*(const Matrix3x3& mat, const yorumathpoint::Point2f& p);
		friend bool operator==(const Matrix3x3& mat1, const Matrix3x3& mat2);

		static Matrix3x3* const identity;
	};
}}

#endif
