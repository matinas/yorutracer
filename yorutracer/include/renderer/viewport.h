#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "math\point2d.h"

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

		math::Point2d<float>* getPoint(float x, float y);

		// takes a point in the viewport local coordinate system (world coordinate) to a point in the specified canvas' local coordinate system (pixel)
		math::Point2d<int> toCanvasCoords(math::Point2d<float> p, Canvas canvas);

	private:
		double width, height;
	};
}}

#endif
