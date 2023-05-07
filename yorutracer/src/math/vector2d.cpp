#include "math\vector2d.h"

namespace yoru {
namespace math {

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

	float Vector2d::getX() const
	{
		return x;
	}

	float Vector2d::getY() const
	{
		return y;
	}
}}