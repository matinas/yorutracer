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

	math::Point2d Viewport::toCanvasCoords(math::Point2d p, Canvas canvas)
	{
		// in the inverse way as toViewportCoords(), we now need to convert a viewport point which
		// represents a pixel in world coordinates to an actual pixel in the canvas, so we just
		// need a scale transform. check more details in Canvas::toViewportCoords()

		math::Scale2d ratio = math::Scale2d(static_cast<float>(canvas.getWidth()) / this->width, static_cast<float>(canvas.getHeight()) / this->height);

		return ratio * p; // FIXME: parameter point p should be a point in the viewport, thus it should have not int but floating-point coords (make Point2d a template class)
	}
}}