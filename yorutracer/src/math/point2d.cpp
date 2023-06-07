#include "math\Point2d.h"

namespace yoru {
namespace math {

	template <typename T> Point2d<T>::Point2d()
	{
		this->x = 0;
		this->y = 0;
	}

	template <typename T> Point2d<T>::Point2d(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	template <typename T> Point2d<T>::~Point2d()
	{
	}

	template <typename T> T Point2d<T>::getX() const
	{
		return x;
	}

	template <typename T> T Point2d<T>::getY() const
	{
		return y;
	}

	// below explicit template instantiations are required to satisfy the linker
	// from https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl (referenced here: https://stackoverflow.com/questions/115703/storing-c-template-function-definitions-in-a-cpp-file)

	template Point2d<int>::Point2d();
	template Point2d<int>::Point2d(int x, int y);
	template Point2d<int>::~Point2d();
	template int Point2d<int>::getX() const;
	template int Point2d<int>::getY() const;

	template Point2d<float>::Point2d();
	template Point2d<float>::Point2d(float x, float y);
	template Point2d<float>::~Point2d();
	template float Point2d<float>::getX() const;
	template float Point2d<float>::getY() const;
}}