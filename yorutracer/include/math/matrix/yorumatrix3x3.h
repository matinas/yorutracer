#ifndef YORUMATRIX3X3_H
#define YORUMATRIX3X3_H

#include "math\matrix\matrix3x3.h"

namespace yoru {
namespace math
{
	class YoruMatrix3x3 : public Matrix3x3
	{
	public:
		YoruMatrix3x3();
		YoruMatrix3x3(float item00, float item01, float item02, float item10, float item11, float item12, float item20, float item21, float item22);
		YoruMatrix3x3(Vector3d row0, Vector3d row1, Vector3d row2);
		YoruMatrix3x3(float mat[3][3]);
		~YoruMatrix3x3();

		float getItem(int i, int j) const;
		Vector3d getRow(int row) const;
		Vector3d getCol(int col) const;

		float det();
		Matrix3x3* transpose();
		Matrix3x3* inverse();

	private:
		float items[3][3];
	};
}}

#endif
