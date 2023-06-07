#include <iostream>

#include "renderer\viewport.h"
#include "renderer\canvas.h"
#include "math\transformation\scale2d.h"

namespace yoru {
namespace renderer {

	Viewport::Viewport()
	{
	}

	Viewport::~Viewport()
	{
	}

	Viewport::Viewport(double width, double height) : width(width), height(height)
	{
	}

	double Viewport::getWidth()
	{
		return this->width;
	}
	
	double Viewport::getHeight()
	{
		return this->height;
	}

	math::Point2d<float>* Viewport::getPoint(float x, float y)
	{
		float halfWidth = width / 2.0f;
		float halfHeight = height / 2.0f;

		if (x < -halfWidth || y < -halfHeight || x > halfWidth || y > halfHeight)
		{
			std::cout << "There's no point in the viewport at (" << x << "," << y << ")\n";

			return NULL;
		}

		return new math::Point2d<float>(x, y);
	}

	math::Point2d<int> Viewport::toCanvasCoords(math::Point2d<float> p, Canvas canvas)
	{
		// in the inverse way as toViewportCoords(), we now need to convert a viewport point which
		// represents a pixel in world coordinates to an actual pixel in the canvas, so we just
		// need a scale transform. check more details in Canvas::toViewportCoords()

		math::Scale2d ratio = math::Scale2d(canvas.getWidth() / this->width, canvas.getHeight() / this->height);
		math::Point2d<float> pScale = ratio * p;

		return math::Point2d<int>(static_cast<int>(pScale.getX()), static_cast<int>(pScale.getY()));
	}
}}