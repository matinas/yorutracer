#ifndef SCREEN_H
#define SCREEN_H

#include "math\point2d.h"
#include "math\matrix\matrix3x3.h"
#include "math\transformation\affine2d.h"

namespace yoru {
namespace renderer {

	class Canvas;

	class Screen
	{
	public:
		Screen();
		Screen(int width, int height);

		// the origin of the screen by (our) convention is at the top/left of the rectangle defined by height/width
		// from the origin x goes right and y goes down (y is mirrored wrt the global 2D/UI world space coordinate system)
		Screen(int width, int height, math::Point2d<int> center);

		~Screen();

		int getWidth();
		int getHeight();

		math::Point2d<int> getCenter();
		math::Point2d<int>* getPoint(int x, int y);

		// the returned transformation allows to take a point in the screen local coordinate system to
		// a point in the global 2D/UI world space coordinate system (z=0) upon which the screen is defined
		math::Affine2d getScreenToWorldTransform();

		// the returned transformation allows to take a point in the 2D/UI world space coordinate (z=0)
		// system upon which the screen is defined, to a point in the screen local coordinate system
		math::Affine2d getWorldToScreenTransform();
		
		// takes a point in the screen local coordinate system to a point in the specified canvas local coordinate system,
		// assuming both coordinate systems are custom-positioned in relation to the global 2D/UI world space coordinate system (z=0)
		math::Point2d<int> toCanvasWorldCoords(math::Point2d<int> p, Canvas screen);

		// takes a point in the screen local coordinate system to a point in the specified canvas local coordinate system, assuming both the scren and the
		// canvas "match" exactly (except for any difference in scale), regardless their relative position in the global 2D/UI world space coordinate system (z=0)
		// use this function whenever just mapping a 2D point inside the screen to a 2D point inside the canvas is needed
		math::Point2d<int> toCanvasCoords(math::Point2d<int> p, Canvas screen);

	private:
		int width, height;
		math::Point2d<int> center;
		math::Affine2d screenToWorldTransform, worldToScreenTransform;

		math::Affine2d getWorldTransform();
		math::Affine2d getScreenToCanvasWorldTransform(Canvas canvas);

		void initTransforms();
	};
}}

#endif
