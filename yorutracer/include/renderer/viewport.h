#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "math\point.h"

namespace yoru {
namespace renderer {

	class Canvas;

	class Viewport
	{
	public:
		Viewport();
		~Viewport();
		Viewport(double width, double height);

		double getWidth();
		double getHeight();

		yorumathpoint::Point2f* getPoint(float x, float y);

		// takes a point in the viewport local coordinate system (world coordinate) to a point in the specified canvas' local coordinate system (pixel)
		yorumathpoint::Point2i toCanvasCoords(yorumathpoint::Point2f p, Canvas canvas);

	private:
		double width, height;
	};
}}

#endif
