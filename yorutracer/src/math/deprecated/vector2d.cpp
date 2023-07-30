#include "math\deprecated\vector2d.h"

namespace yoru {
namespace math {
namespace deprecated {

	Vector2d::Vector2d()
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}

	Vector2d::Vector2d(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2d::~Vector2d()
	{
	}

	inline float Vector2d::getX() const
	{
		return x;
	}

	inline float Vector2d::getY() const
	{
		return y;
	}
}}}