#include <iostream>

#include "renderer\canvas.h"
#include "renderer\screen.h"
#include "math\transformation\scale2d.h"
#include "math\transformation\translation2d.h"

namespace yoru {
namespace renderer {

	Screen::Screen()
	{
		this->width = 800;
		this->height = 600;
		this->center = math::Point2d<int>(0, 0); // when not specified the center of the canvas matches the origin in global 2D/UI world space coordinates

		initTransforms();
	}

	Screen::Screen(int width, int height) : width(width), height(height)
	{
		this->center = math::Point2d<int>(0, 0);

		initTransforms();
	}

	// creates a screen with a custom center specified relative to the
	// global 2D/UI world space coordinate system origin which is at (0,0)
	Screen::Screen(int width, int height, math::Point2d<int> center) : width(width), height(height), center(center)
	{
		initTransforms();
	}

	void Screen::initTransforms()
	{
		screenToWorldTransform = getWorldTransform();
		worldToScreenTransform = screenToWorldTransform.inverse();
	}

	Screen::~Screen()
	{
	}

	math::Affine2d Screen::getWorldTransform()
	{
		math::Translation2d translation = math::Translation2d(static_cast<float>(this->center.getX()), static_cast<float>(-this->center.getY()));
		math::Scale2d mirror = math::Scale2d(1.0f, -1.0f);

		return math::Affine2d(&translation, &mirror);
	}

	int Screen::getWidth()
	{
		return this->width;
	}

	int Screen::getHeight()
	{
		return this->height;
	}

	math::Point2d<int> Screen::getCenter()
	{
		return this->center;
	}

	math::Affine2d Screen::getScreenToWorldTransform()
	{
		return screenToWorldTransform;
	}

	math::Affine2d Screen::getWorldToScreenTransform()
	{
		return worldToScreenTransform;
	}

	math::Affine2d Screen::getScreenToCanvasWorldTransform(Canvas canvas)
	{
		// TODO: take into account the eventual difference in scale between canvas and screen

		math::Affine2d screenToCanvas = canvas.getWorldToCanvasTransform() * this->screenToWorldTransform;

		return screenToCanvas;
	}

	math::Point2d<int> Screen::toCanvasWorldCoords(math::Point2d<int> p, Canvas canvas)
	{
		return getScreenToCanvasWorldTransform(canvas) * p;
	}

	math::Point2d<int> Screen::toCanvasCoords(math::Point2d<int> p, Canvas canvas)
	{
		// TODO: take into account the eventual difference in scale between canvas and screen
		
		// we know that Ps=(200,200) should map to Pc=(100,-100), and Ps'=(100,100) to Pc'(0,0) (Ps=screen point, Pc=canvas point)
		// so we need to find the matrix M so that M*Ps=Pc and M*Ps'=Pc'
		// where M has the following layout: | Sx 0  Tx | 
		//									 | 0  Sy Ty | (we know it's enough with a scaling so to mirror the Y plus a translation)
		//									 | 0  0  1  |
		// usign both of the already known mappings we get a linear equation system with 4 equations and 4 variables
		// we can easily resolve it to get: Sx=1, Sy=-1, Tx=-100 (-Sw/2), and Ty=100 (Sh/2)
		// then, the transformation that maps a screen point to a canvas point is T*S

		math::Scale2d mirror = math::Scale2d(1.0f, -1.0f);
		math::Translation2d translation = math::Translation2d(static_cast<float>(-width*0.5f), static_cast<float>(height*0.5f));

		math::Affine2d transform = math::Affine2d(nullptr, &mirror, &translation);

		math::Scale2d ratio = math::Scale2d(static_cast<float>(canvas.getWidth()) / this->width, static_cast<float>(canvas.getHeight()) / this->height);

		return ratio * transform * p;
	}

	math::Point2d<int>* Screen::getPoint(int x, int y)
	{
		if (x < 0 || y < 0 || x > width || y > height)
		{
			std::cout << "There's no point in the screen at (" << x << "," << y << ")\n";

			return NULL;
		}

		return new math::Point2d<int>(x, y);
	}
}}