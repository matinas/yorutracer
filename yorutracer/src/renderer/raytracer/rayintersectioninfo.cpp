#include <iostream>

#include "renderer\raytracer\rayintersectioninfo.h"

namespace yoru {
namespace renderer {

	RayIntersectionInfo::RayIntersectionInfo()
	{
	}

	RayIntersectionInfo::RayIntersectionInfo(Ray* const ray, objects::Sphere* const sphere, yorumathpoint::Point3f* const points)
	{
		this->ray = ray;
		this->sphere = sphere;
		this->points = points;
	}

	RayIntersectionInfo::~RayIntersectionInfo()
	{
	}

	Ray* RayIntersectionInfo::getRay() const
	{
		return ray;
	}

	objects::Sphere* RayIntersectionInfo::getSphere() const
	{
		return sphere;
	}

	bool RayIntersectionInfo::hasHits()
	{
		return this->points != nullptr;
	}

	yorumathpoint::Point3f* RayIntersectionInfo::getPoints()
	{
		return points;
	}

	yorumathpoint::Point3f* RayIntersectionInfo::getNearest()
	{
		if (points != nullptr)
		{
			yorumathpoint::Point3f rayOrigin = ray->getOrigin();

			float dist1 = rayOrigin.distanceTo(points[0]);
			float dist2 = rayOrigin.distanceTo(points[1]);
		
			return dist1 <= dist2 ? &points[0] : &points[1];
		}
		else
		{
			std::cout << "Can't get the nearest point as there are no hits registered\n";

			return nullptr;
		}
	}

}}
