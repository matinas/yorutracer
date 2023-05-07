#include <glm\glm.hpp>

#include "objects\sphere.h"
#include "ray.h"

using namespace yorutracer;
using namespace yorutracer::objects;

Sphere::Sphere()
{
	this->center = glm::vec3(0.f);
	this->radius = 1;
}

Sphere::Sphere(glm::vec3 center, float radius)
{
	this->center = center;
	this->radius = radius;
}

Sphere::~Sphere()
{
}

glm::vec3 Sphere::get_center()
{
	return center;
}

float Sphere::get_radius()
{
	return radius;
}

RayIntersectionInfo Sphere::intersect(Ray ray)
{
	RayIntersectionInfo intersection_info;

	glm::vec3 D = glm::normalize(ray.get_destination() - ray.get_origin());
	glm::vec3 CO = ray.get_origin() - this->center;
	float D_CO_dot = glm::dot(D,CO);
	float CO_dot = glm::dot(CO,CO);

	float a = glm::dot(D,D);
	float b = 2 * D_CO_dot;
	float c = CO_dot - this->radius * this->radius;

	float det = b*b - 4*a*c;
	if (det < 0)
	{
		intersection_info = RayIntersectionInfo(&ray, this, NULL);
	}
	else
	{
		int root_count = (det == 0) ? 1 : 2;

		float* roots = new float[root_count];
		for (int i=0, j=1; i<root_count; ++i, j=j-2) // when there are two roots j takes values 1 and -1 (trick to use a generic formula below)
		{
			roots[i] = (-b + j*sqrt(det)) / 2*a;
		}

		glm::vec3* points = new glm::vec3[root_count];

		for (int i=0; i<root_count; i++)
		{
			points[i] = ray.get_origin() + roots[i] * D;
		}

		intersection_info = RayIntersectionInfo(&ray, this, points);
	}

	return intersection_info;
}
