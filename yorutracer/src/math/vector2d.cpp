#include "yoru\math\vector2d.h"

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

float Vector2d::getX()
{
	return x;
}

float Vector2d::getY()
{
	return y;
}