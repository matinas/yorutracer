#ifndef VECTOR2D_H
#define VECTOR2D_H

// deprecated
// use the more generic math::Vector<T,D>

namespace yoru {
namespace math {
namespace deprecated {

	class Vector2d
	{
	public:
		Vector2d();
		Vector2d(float x, float y);
		~Vector2d();

		inline float getX() const;
		inline float getY() const;

	private:
		float x, y;
	};

	typedef Vector2d Vector2f; // we define this in this way so as to be able to refer to either this deprecated Vector2d or the newer more generic Vector<T,2>
							   // as Vector2f (one inside yoru::math and the other inside yoru::math::deprecated). switching between one or the other is just
							   // a matter of defining USE_DEPRECATED_VECTOR inside commons.h (which ends up setting the proper namespace alias yorumathvector)
}}}

#endif
