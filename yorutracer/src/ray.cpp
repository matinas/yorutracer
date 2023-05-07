#include "ray.h"

using namespace yorutracer;

Ray::Ray()
{
	this->origin = glm::vec3(0.f);
	this->destination = glm::vec3(0.f,0.f,1.f);
}

Ray::Ray(glm::vec3 origin, glm::vec3 destination)
{
	this->origin = origin;
	this->destination = destination;
}

Ray::~Ray()
{
}

glm::vec3 Ray::get_origin()
{
	return origin;
}

glm::vec3 Ray::get_destination()
{
	return destination;
}