#include "renderer\raytracer\ray.h"

using namespace yoru;

Ray::Ray()
{
	this->origin = math::Point3d(0.f,0.f,0.f);
	this->destination = math::Point3d(0.f,0.f,1.f);
}

Ray::Ray(const math::Point3d& origin, const math::Point3d& destination)
{
	this->origin = origin;
	this->destination = destination;
}

Ray::~Ray()
{
}

math::Point3d Ray::getOrigin() const
{
	return origin;
}

math::Point3d Ray::getDestination() const
{
	return destination;
}