#include "math\matrix\matrixfactory.h"
#include "math\matrix\glmmatrix3x3.h"
#include "math\matrix\yorumatrix3x3.h"

namespace yoru {
namespace math {

	Matrix3x3* MatrixFactory::getMatrix(float item00, float item01, float item02, float item10, float item11, float item12, float item20, float item21, float item22)
	{
		if (USE_GLM)
		{
			return new GLMMatrix3x3(item00, item01, item02,
									item10, item11, item12,
									item20, item21, item22);
		}
		else
		{
			return new YoruMatrix3x3(item00, item01, item02,
									 item10, item11, item12,
									 item20, item21, item22);
		}
	}

	Matrix3x3* MatrixFactory::getMatrix(const Vector3d& row0, const Vector3d& row1, const Vector3d& row2)
	{
		if (USE_GLM)
		{
			return new GLMMatrix3x3(row0, row1, row2);
		}
		else
		{
			return new YoruMatrix3x3(row0, row1, row2);
		}
	}
}}