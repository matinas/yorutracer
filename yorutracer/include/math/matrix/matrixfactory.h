#ifndef MATRIX3X3_FACTORY_H
#define MATRIX3X3_FACTORY_H

#include "math\vector.h"
#include "math\matrix\matrix3x3.h"

namespace yoru {
namespace math
{
	// as we wanted to support both our custom implementation of the matrix module, but also the one
	// from the GLM library, this factory allows to transparently construct a matrix using the proper
	// module (specified in the settings module in the future)

	class MatrixFactory
	{
	public:
		static Matrix3x3* getMatrix(float item00, float item01, float item02, float item10, float item11, float item12, float item20, float item21, float item22);
		static Matrix3x3* getMatrix(const yorumathvector::Vector3f& row0, const yorumathvector::Vector3f& row1, const yorumathvector::Vector3f& row2);

	private:
	};
}}

#endif
