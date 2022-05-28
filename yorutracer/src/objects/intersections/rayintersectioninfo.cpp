#include "yoru\objects\intersections\rayintersectioninfo.h"

#include <glm\glm.hpp>

using namespace yorutracer;
using namespace yorutracer::objects;

RayIntersectionInfo::RayIntersectionInfo()
{
}

RayIntersectionInfo::RayIntersectionInfo(Ray* const ray, Sphere* const sphere, glm::vec3* const points)
{
	this->ray = ray;
	this->sphere = sphere;

	this->points = points;
}

RayIntersectionInfo::~RayIntersectionInfo()
{
}

Ray* RayIntersectionInfo::get_ray()
{
	return ray;
}

Sphere* RayIntersectionInfo::get_sphere()
{
	return sphere;
}

bool RayIntersectionInfo::exist()
{
	return this->points != NULL;
}

glm::vec3* RayIntersectionInfo::get_points()
{
	return points;
}

glm::vec3* RayIntersectionInfo::get_nearest()
{
	if (points != NULL)
	{
		float dist1 = glm::distance(ray->get_origin(), points[0]);
		float dist2 = glm::distance(ray->get_origin(), points[1]);
		
		return dist1 < dist2 ? &points[0] : &points[1];
	}
	else
		return NULL;
}