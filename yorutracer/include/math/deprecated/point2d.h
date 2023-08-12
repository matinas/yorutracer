#ifndef POINT2D_H
#define POINT2D_H

namespace yoru {
namespace math {
namespace deprecated {

	template <typename T>
	class Point2d
	{
	public:
		Point2d();
		Point2d(T x, T y);
		~Point2d();

		T getX() const;
		T getY() const;

	private:
		T x, y;
	};

	typedef Point2d<int> Point2i;   // we define these in this way so as to be able to refer to either this deprecated Point2d or the newer more generic Point<T,2>
	typedef Point2d<float> Point2f; // as Point2i/Point2f (one inside yoru::math and the other inside yoru::math::deprecated). switching between one or the other
									// is just a matter of defining USE_DEPRECATED_POINT inside common.h (which ends up setting the proper namespace alias yorumathpoint)
}}}

#endif

