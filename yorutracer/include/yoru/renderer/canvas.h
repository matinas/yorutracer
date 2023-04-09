#ifndef CANVAS_H
#define CANVAS_H

#include "yoru\math\point2d.h"
#include "yoru\math\matrix3x3.h"

const int myConst = 10;

class Canvas
{
public:
	Canvas();
	Canvas(int width, int height);
	Canvas(int width, int height, Point2d center); // the center of the canvas by convention is at the center of the rectangle defined by height/width
	~Canvas();									   // from the center x goes right and y goes up (same as the global 2D/UI world space coordinate system)

	int getWidth();
	int getHeight();
	Point2d getCenter();
	Point2d* getPoint(int x, int y);

	Matrix3x3 getCanvasToWorldTransform();

private:
	int width, height;
	Point2d center;
	Matrix3x3 canvasToWorldTransform;
	Matrix3x3 worldToCanvasTransform;
};

#endif
