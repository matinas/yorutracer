#ifndef POINT2D_H
#define POINT2D_H

namespace yoru {
namespace math {

	// TODO: include the dimension as part of the template so to make it even more flexible
	// https://studiofreya.com/cpp/cpp-templates/cpp-class-template-example-point-and-point3d/

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
}}

#endif

