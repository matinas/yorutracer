#include "math\matrix\glmmatrix3x3.h"

namespace yoru {
namespace math {

	GLMMatrix3x3::GLMMatrix3x3()
	{
	}

	GLMMatrix3x3::GLMMatrix3x3(glm::mat3x3 mat)
	{
		this->matrix = mat;
	}

	GLMMatrix3x3::GLMMatrix3x3(float item00, float item01, float item02,
							   float item10, float item11, float item12,
							   float item20, float item21, float item22)
	{
		matrix = glm::mat3x3(item00, item01, item02,
							 item10, item11, item12,
							 item20, item21, item22);
	}

	GLMMatrix3x3::GLMMatrix3x3(Vector3d row0, Vector3d row1, Vector3d row2)
	{
		glm::vec3 vrow0 = glm::vec3(row0.getX(), row0.getY(), row0.getZ());
		glm::vec3 vrow1 = glm::vec3(row1.getX(), row1.getY(), row1.getZ());
		glm::vec3 vrow2 = glm::vec3(row2.getX(), row2.getY(), row2.getZ());

		matrix = glm::mat3x3(vrow0, vrow1, vrow2);
	}

	GLMMatrix3x3::GLMMatrix3x3(float items[3][3])
	{
		matrix = glm::mat3x3(items[0][0], items[0][1], items[0][2],
							 items[1][0], items[1][1], items[1][2],
							 items[2][0], items[2][1], items[2][2]);
	}

	GLMMatrix3x3::~GLMMatrix3x3()
	{
	}

	float GLMMatrix3x3::getItem(int i, int j) const
	{
		return matrix[i][j];
	}

	Vector3d GLMMatrix3x3::getRow(int row) const
	{
		return Vector3d(matrix[row][0], matrix[row][1], matrix[row][2]);
	}

	Vector3d GLMMatrix3x3::getCol(int col) const
	{
		return Vector3d(matrix[0][col], matrix[1][col], matrix[2][col]);
	}

	float GLMMatrix3x3::det()
	{
		return glm::determinant(matrix);
	}

	Matrix3x3* GLMMatrix3x3::inverse()
	{
		glm::mat3x3 inv = glm::inverse(matrix);

		return new GLMMatrix3x3(inv[0][0], inv[0][1], inv[0][2],
								inv[1][0], inv[1][1], inv[1][2],
								inv[2][0], inv[2][1], inv[2][2]);
	}

	Matrix3x3* GLMMatrix3x3::transpose()
	{
		glm::mat3x3 transp = glm::transpose(matrix);

		return new GLMMatrix3x3(transp[0][0], transp[0][1], transp[0][2],
								transp[1][0], transp[1][1], transp[1][2],
								transp[2][0], transp[2][1], transp[2][2]);
	}

	GLMMatrix3x3* operator*(const GLMMatrix3x3& mat1, const GLMMatrix3x3& mat2)
	{
		glm::mat3x3 mat = mat1.matrix * mat2.matrix;

		return new GLMMatrix3x3(mat);
	}
}}