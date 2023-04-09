#ifndef SCREEN_H
#define SCREEN_H

#include "yoru\math\point2d.h"
#include "yoru\math\matrix3x3.h"

class Screen
{
public:
	Screen();
	Screen(int width, int height);
	Screen(int width, int height, Point2d center); // the center of the screen by convention is at the top/left of the rectangle defined by height/width
	~Screen();									   // from the center x goes right and y goes down (y is mirrored wrt the global 2D/UI world space coordinate system)

	int getWidth();
	int getHeight();
	Point2d getCenter();
	Point2d* getPoint(int x, int y);

	Point2d toScreenCoords(Point2d);
	Matrix3x3 getScreenToWorldTransform();
	Matrix3x3 getWorldToScreenTransform();

private:
	int width, height;
	Point2d center;
	Matrix3x3 screenToWorldTransform, worldToScreenTransform;
};

#endif
