#include "yoru\math\point2d.h"

Point2d::Point2d()
{
	this->x = 0;
	this->y = 0;
}

Point2d::Point2d(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point2d::~Point2d()
{

}

int Point2d::getX() const
{
	return x;
}

int Point2d::getY() const
{
	return y;
}