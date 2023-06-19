#include <iostream>

#include "renderer\raytracer\rayintersectioninfo.h"

namespace yoru {
namespace renderer {

	RayIntersectionInfo::RayIntersectionInfo()
	{
	}

	RayIntersectionInfo::RayIntersectionInfo(Ray* const ray, objects::Sphere* const sphere, math::Point3d* const points)
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

	math::Point3d* RayIntersectionInfo::getPoints()
	{
		return points;
	}

	math::Point3d* RayIntersectionInfo::getNearest()
	{
		if (points != nullptr)
		{
			math::Point3d rayOrigin = ray->getOrigin();

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
