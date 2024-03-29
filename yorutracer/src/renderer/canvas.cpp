#include <iostream>

#include "renderer\screen.h"
#include "renderer\canvas.h"
#include "renderer\camera.h"
#include "math\transformation\translation2d.h"
#include "math\transformation\scale2d.h"

namespace yoru {
namespace renderer {

	Canvas::Canvas()
	{
		this->width = 800;
		this->height = 600;
		this->center = yorumathpoint::Point2i(0, 0); // when not specified, the center of the canvas matches the origin (0,0) of the global 2D/UI world space coordinates

		this->halfWidth = static_cast<float>(this->width*0.5f);
		this->halfHeight = static_cast<float>(this->height*0.5f);

		initTransforms();
	}

	Canvas::Canvas(int width, int height) : width(width), height(height), halfWidth(static_cast<float>(width*0.5f)), halfHeight(static_cast<float>(height*0.5f))
	{
		this->center = yorumathpoint::Point2i(0, 0);

		initTransforms();
	}

	Canvas::Canvas(int width, int height, yorumathpoint::Point2i center) : width(width), height(height), halfWidth(static_cast<float>(width*0.5f)), halfHeight(static_cast<float>(height*0.5f)), center(center)
	{
		initTransforms();
	}

	void Canvas::initTransforms()
	{
		canvasToWorldTransform = getWorldTransform();
		worldToCanvasTransform = canvasToWorldTransform.inverse();

		// cache the base of the screen coords transform so we don't need to calculate it each time we make a call
		// to toScreenCoords (which is quite often, as we are calling it for each pixel when rendering via raytracing)
		math::Scale2d mirror = math::Scale2d(1.0f, -1.0f);
		math::Translation2d translation = math::Translation2d(halfWidth, halfHeight);
		screenCoordsTransform = math::Affine2d(&mirror, &translation);
	}

	Canvas::~Canvas()
	{
	}

	math::Affine2d Canvas::getWorldTransform()
	{
		return math::Translation2d(static_cast<float>(this->center.getX()), static_cast<float>(this->center.getY()));
	}

	int Canvas::getWidth()
	{
		return this->width;
	}

	int Canvas::getHeight()
	{
		return this->height;
	}

	yorumathpoint::Point2i Canvas::getCenter()
	{
		return this->center;
	}

	math::Affine2d Canvas::getCanvasToWorldTransform()
	{
		return this->canvasToWorldTransform;
	}

	math::Affine2d Canvas::getWorldToCanvasTransform()
	{
		return this->worldToCanvasTransform;
	}

	math::Affine2d Canvas::getCanvasToScreenWorldTransform(Screen screen)
	{
		math::Affine2d canvasToScreen = screen.getWorldToScreenTransform() * this->canvasToWorldTransform;

		return canvasToScreen;
	}

	yorumathpoint::Point2i Canvas::toScreenWorldCoords(yorumathpoint::Point2i p, Screen screen)
	{
		return getCanvasToScreenWorldTransform(screen) * p;
	}

	yorumathpoint::Point2i Canvas::toScreenCoords(yorumathpoint::Point2i p, Screen screen)
	{
		// we know that Pc=(100,100) should map to Ps=(200,0), and Pc'=(100,-100) to Ps'(200,200) (Pc=canvas point, Ps=screen point)
		// so we need to find the matrix M so that M*Pc=Ps and M*Pc'=Ps'
		// where M has the following layout: | Sx 0  Tx | 
		//									 | 0  Sy Ty | (we know it's enough with a scaling so to mirror the Y plus a translation)
		//									 | 0  0  1  |
		// usign both of the already known mappings we get a linear equation system with 4 equations and 4 variables
		// we can easily resolve it to get: Sx=1, Sy=-1, Tx=100 (Cw/2), and Ty=100 (Ch/2)
		// then, the transformation that maps a screen point to a canvas point is T*S

		if ((screen.getWidth() != this->width) || (screen.getHeight() != this->height)) // avoids processing ratio if screen and canvas are the same size (commonly the case!)
		{
			math::Scale2d ratio = math::Scale2d(static_cast<float>(screen.getWidth()) / this->width, static_cast<float>(screen.getHeight()) / this->height);

			return ratio * screenCoordsTransform * p; // apply the ratio at the end so to take into account any size difference between canvas and screen
		}
		else
		{
			return screenCoordsTransform * p;
		}
	}

	yorumathpoint::Point3f Canvas::toViewportCoords(yorumathpoint::Point2i p, Camera camera)
	{
		// as both the canvas and the viewport coordinate systems are conveniently defined to "match", the only thing we need to
		// take into account is the difference in scale between canvas and viewport, given the viewport is measured in world units
		// (e.g.: Vw=Vh=1 commonly used) and the canvas is measured in pixels (e.g.: Cx=1920, Cy=1080). basically, we need to "divide"
		// the viewport in the same amount of pixels than the canvas, to get the corresponding canvas pixel into world space coordinates

		renderer::Viewport viewport = camera.getViewport();
		yorumathpoint::Point3f point = yorumathpoint::Point3f(static_cast<float>(p.getX()), static_cast<float>(p.getY()), camera.getNear());

		if ((viewport.getWidth() != this->width) || (viewport.getHeight() != this->height)) // avoids processing ratio if viewport and canvas are the same size (not commonly the case though)
		{
			math::Scale2d ratio = math::Scale2d(viewport.getWidth() / this->width, viewport.getHeight() / this->height);

			return ratio * point;
		}

		return point;
	}

	yorumathpoint::Point2i* Canvas::getPoint(int x, int y)
	{
		if (x < -halfWidth || y < -halfHeight || x > halfWidth || y > halfHeight)
		{
			std::cout << "There's no point in the canvas at (" << x << "," << y << ")\n";

			return NULL;
		}

		return new yorumathpoint::Point2i(x, y);
	}
}}