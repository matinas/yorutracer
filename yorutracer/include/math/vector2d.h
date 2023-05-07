#ifndef VECTOR2D_H
#define VECTOR2D_H

namespace yoru {
namespace math {

	class Vector2d
	{
	public:
		Vector2d();
		Vector2d(float x, float y);
		~Vector2d();

		float getX() const;
		float getY() const;

	private:
		float x, y;
	};
}}

#endif