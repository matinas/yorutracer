#ifndef CANVAS_H
#define CANVAS_H

#include "math\point2d.h"
#include "math\matrix3x3.h"
#include "math\transformation\affine2d.h"

namespace yoru {
namespace renderer {

	class Screen;

	class Canvas
	{
	public:
		Canvas();
		Canvas(int width, int height);

		// creates a canvas with a custom center relative to the global 2D/UI world space coordinate system origin which is at (0,0)
		// the origin of the canvas by (our) convention is at the center of the rectangle defined by width/height
		// starting from the center, x goes right and y goes up, in the same way as the global 2D/UI world space coordinate system (z=0)
		Canvas(int width, int height, math::Point2d center);

		~Canvas();

		int getWidth();
		int getHeight();

		math::Point2d getCenter();
		math::Point2d* getPoint(int x, int y);

		// the returned transformation allows to take a point in the canvas local coordinate system to
		// a point in the global 2D/UI world space coordinate system (z=0) upon which the canvas is defined
		math::Affine2d getCanvasToWorldTransform();

		// the returned transformation allows to take a point in the 2D/UI world space coordinate (z=0)
		// system upon which the canvas is defined, to a point in the canvas local coordinate system
		math::Affine2d getWorldToCanvasTransform();

		// takes a point in the canvas local coordinate system to a point in the specified screen local coordinate system,
		// assuming both coordinate systems are custom-positioned in relation to the global 2D/UI world space coordinate system (z=0)
		math::Point2d toScreenWorldCoords(math::Point2d p, Screen screen);

		// takes a point in the canvas local coordinate system to a point in the specified screen local coordinate system, assuming both the canvas and the
		// screen "match" exactly (except for any difference in scale), regardless their relative position in the global 2D/UI world space coordinate system (z=0)
		// use this function whenever just mapping a 2D point inside the canvas to a 2D point inside the screen is needed
		math::Point2d toScreenCoords(math::Point2d p, Screen screen);

	private:
		int width, height;
		math::Point2d center;
		math::Affine2d canvasToWorldTransform, worldToCanvasTransform;
		
		math::Affine2d getWorldTransform();
		math::Affine2d getCanvasToScreenWorldTransform(Screen screen);

		void initTransforms();
	};
}}

#endif
