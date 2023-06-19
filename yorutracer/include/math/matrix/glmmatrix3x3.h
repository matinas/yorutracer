#ifndef GLMMATRIX3X3_H
#define GLMMATRIX3X3_H

#include <glm\glm.hpp>

#include "math\matrix\matrix3x3.h"

namespace yoru {
namespace math
{
	class GLMMatrix3x3 : public Matrix3x3
	{
	public:
		GLMMatrix3x3();
		GLMMatrix3x3(const glm::mat3x3& mat);
		GLMMatrix3x3(float item00, float item01, float item02, float item10, float item11, float item12, float item20, float item21, float item22);
		GLMMatrix3x3(const Vector3d& row0, const Vector3d& row1, const Vector3d& row2);
		GLMMatrix3x3(float mat[3][3]);
		~GLMMatrix3x3();

		float getItem(int i, int j) const;
		Vector3d getRow(int row) const;
		Vector3d getCol(int col) const;

		float det();
		Matrix3x3* transpose();
		Matrix3x3* inverse();

		friend GLMMatrix3x3* operator*(const GLMMatrix3x3& mat1, const GLMMatrix3x3& mat2);

	private:
		glm::mat3x3 matrix;
	};
}}

#endif
