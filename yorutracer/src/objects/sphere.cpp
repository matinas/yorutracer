#include <math.h>

#include "objects\sphere.h"
#include "renderer\raytracer\ray.h"
#include "utils\utils.h"

using namespace yoru;
using namespace yoru::objects;

Sphere::Sphere()
{
	this->center = yorumathpoint::Point3f(0.f,0.f,0.f);
	this->radius = 1.f;
}

Sphere::Sphere(const yorumathpoint::Point3f& center, float radius)
{
	this->center = center;
	this->radius = radius;
	this->color = yorumathpoint::Point3f(0.988f, 0.0588f, 0.7529f); // bright pink = (252, 15, 192)
}

Sphere::Sphere(const yorumathpoint::Point3f& center, float radius, const yorumathpoint::Point3f& color)
{
	this->center = center;
	this->radius = radius;
	this->color = color;
}

Sphere::~Sphere()
{
}

yorumathpoint::Point3f Sphere::getCenter() const
{
	return center;
}

float Sphere::getRadius() const
{
	return radius;
}

yorumathpoint::Point3f Sphere::getColor() const
{
	return color;
}

renderer::RayIntersectionInfo Sphere::intersect(Ray ray)
{
	renderer::RayIntersectionInfo intersection_info;

	yorumathvector::Vector3f D = ray.getDestination() - ray.getOrigin();
	D.normalize();
	yorumathvector::Vector3f CO = ray.getOrigin() - this->center;
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
		
		yorumathpoint::Point3f* points = new yorumathpoint::Point3f[root_count];

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
