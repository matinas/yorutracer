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

		math::Point2d toCanvasCoords(math::Point2d p, Canvas canvas);

	private:
		double width, height;
	};
}}

#endif
