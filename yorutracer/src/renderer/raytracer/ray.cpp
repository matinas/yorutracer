#include "renderer\raytracer\ray.h"

using namespace yoru;

Ray::Ray()
{
	this->origin = yorumathpoint::Point3f(0.f,0.f,0.f);
	this->destination = yorumathpoint::Point3f(0.f,0.f,1.f);
}

Ray::Ray(const yorumathpoint::Point3f& origin, const yorumathpoint::Point3f& destination)
{
	this->origin = origin;
	this->destination = destination;
}

Ray::~Ray()
{
}

yorumathpoint::Point3f Ray::getOrigin() const
{
	return origin;
}

yorumathpoint::Point3f Ray::getDestination() const
{
	return destination;
}