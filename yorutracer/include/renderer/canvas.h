#ifndef CANVAS_H
#define CANVAS_H

#include "math\point.h"
#include "math\matrix\matrix3x3.h"
#include "math\transformation\affine2d.h"

namespace yoru {
namespace renderer {

	class Screen;
	class Camera;

	class Canvas
	{
	public:
		Canvas();
		Canvas(int width, int height);

		// creates a canvas with a custom center relative to the global 2D/UI world space coordinate system origin which is at (0,0)
		// the origin of the canvas by (our) convention is at the center of the rectangle defined by width/height
		// starting from the origin, x goes right and y goes up, in the same way as the global 2D/UI world space coordinate system (z=0)
		Canvas(int width, int height, yorumathpoint::Point2i center);

		~Canvas();

		int getWidth();
		int getHeight();

		yorumathpoint::Point2i getCenter();
		yorumathpoint::Point2i* getPoint(int x, int y);

		// the returned transformation allows to take a point in the canvas local coordinate system to
		// a point in the global 2D/UI world space coordinate system (z=0) upon which the canvas is defined
		math::Affine2d getCanvasToWorldTransform();

		// the returned transformation allows to take a point in the 2D/UI world space coordinate (z=0)
		// system upon which the canvas is defined, to a point in the canvas local coordinate system
		math::Affine2d getWorldToCanvasTransform();

		// takes a point in the canvas local coordinate system to a point in the specified screen local coordinate system,
		// assuming both coordinate systems are custom-positioned in relation to the global 2D/UI world space coordinate system (z=0)
		yorumathpoint::Point2i toScreenWorldCoords(yorumathpoint::Point2i p, Screen screen);

		// takes a point in the canvas local coordinate system to a point in the specified screen local coordinate system, assuming both the canvas and the
		// screen "match" exactly (except for any difference in scale), regardless their relative position in the global 2D/UI world space coordinate system (z=0)
		// use this function whenever just mapping a 2D point inside the canvas to a 2D point inside the screen is needed
		yorumathpoint::Point2i toScreenCoords(yorumathpoint::Point2i p, Screen screen);

		// takes a point in the canvas local coordinate system (pixel) to a point in the specified camera's viewport local coordinate system (world coordinate)
		yorumathpoint::Point3f toViewportCoords(yorumathpoint::Point2i p, Camera camera);

	private:
		int width, height, halfWidth, halfHeight;
		yorumathpoint::Point2i center;
		math::Affine2d canvasToWorldTransform, worldToCanvasTransform, screenCoordsTransform;
		
		math::Affine2d getWorldTransform();
		math::Affine2d getCanvasToScreenWorldTransform(Screen screen);

		void initTransforms();
	};
}}

#endif
