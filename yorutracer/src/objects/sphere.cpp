#include <math.h>

#include "objects\sphere.h"
#include "renderer\raytracer\ray.h"
#include "utils\utils.h"

using namespace yoru;
using namespace yoru::objects;

Sphere::Sphere()
{
	this->center = math::Point3d(0.f,0.f,0.f);
	this->radius = 1.f;
}

Sphere::Sphere(const math::Point3d& center, float radius)
{
	this->center = center;
	this->radius = radius;
	this->color = math::Point3d(0.988f, 0.0588f, 0.7529f); // bright pink = (252, 15, 192)
}

Sphere::Sphere(const math::Point3d& center, float radius, const math::Point3d& color)
{
	this->center = center;
	this->radius = radius;
	this->color = color;
}

Sphere::~Sphere()
{
}

math::Point3d Sphere::getCenter() const
{
	return center;
}

float Sphere::getRadius() const
{
	return radius;
}

math::Point3d Sphere::getColor() const
{
	return color;
}

renderer::RayIntersectionInfo Sphere::intersect(Ray ray)
{
	renderer::RayIntersectionInfo intersection_info;

	math::Vector3d D = ray.getDestination() - ray.getOrigin();
	D.normalize();
	math::Vector3d CO = ray.getOrigin() - this->center;
	float D_CO_dot = D * CO;
	float CO_dot = CO * CO;

	float a = D * D;
	float b = 2 * D_CO_dot;
	float c = CO_dot - (this->radius * this->radius);

	float discriminant = b*b - 4*a*c;
	if (discriminant < 0)
	{
		intersection_info = renderer::RayIntersectionInfo(&ray, this, nullptr); // no real roots, so no intersection
	}
	else
	{
		int root_count = (utils::almostEqual(discriminant, 0.0, 0.001)) ? 1 : 2;
		
		math::Point3d* points = new math::Point3d[root_count];

		float denom = 1.f / 2*a;
		for (int i=0, j=1; i<root_count; ++i, j=j-2) // little trick to use a generic formula below: when there are two roots, j takes values 1 and -1
		{
			float root = (-b + j*sqrt(discriminant)) * denom;
			points[i] = ray.getOrigin() + (root * D);
		}

		intersection_info = renderer::RayIntersectionInfo(&ray, this, points);
	}

	return intersection_info;
}

void Sphere::transform(math::Matrix3x3* transform)
{
	this->center = *transform * this->center;
}
