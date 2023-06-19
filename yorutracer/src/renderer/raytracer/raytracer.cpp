#include <iostream>

#include "renderer\raytracer\raytracer.h"
#include "renderer\raytracer\ray.h"
#include "renderer\raytracer\rayintersectioninfo.h"

#include "objects\sphere.h"

#include "utils\utils.h"

RGBQUAD rgb_black = {0,0,0};
RGBQUAD rgb_blue = {255,0,0};

namespace yoru {
namespace renderer {

	Raytracer::Raytracer(const Canvas& canvas, const Screen& screen, const Camera& camera)
	{
		this->canvas = canvas;
		this->screen = screen;
		this->camera = camera;

		FreeImage_Initialise();

		bitmap = FreeImage_Allocate(IMAGE_HEIGHT, IMAGE_WIDTH, 24);

		if (bitmap)
		{
			std::cout << "Bitmap successfully created" << std::endl;
		}
		else
		{
			std::cout << "There was a problem generating bitmap" << std::endl;
			return;
		}
	}

	Raytracer::~Raytracer()
	{
	}

	void Raytracer::render()
	{
		// FIXME: scene objects must be handled separately, this is temporary here just to quickly test rendering
		yoru::objects::Sphere sphere = yoru::objects::Sphere(math::Point3d(0.f,0.f,3.0f), 1.0f);

		int width = canvas.getWidth();
		int height = canvas.getHeight();

		for (int i=-width/2; i<width/2; ++i)
		{
			for (int j=-height/2; j<height/2; ++j)
			{
				RGBQUAD rgb;

				math::Point3d viewportPoint = canvas.toViewportCoords(math::Point2d<int>(i,j), camera);

				Ray ray = Ray(camera.getOrigin(), viewportPoint);
				RayIntersectionInfo hitInfo = sphere.intersect(ray);

				if (hitInfo.hasHits())
				{
					math::Point3d* point = hitInfo.getNearest();

					rgb = rgb_blue;
				}
				else // there's no interesection
				{
					rgb = rgb_black;
				}

				math::Point2d<int> screenPoint = canvas.toScreenCoords(math::Point2d<int>(i,j), screen);

				FreeImage_SetPixelColor(bitmap, screenPoint.getX(), screenPoint.getY(), &rgb);
			}
		}

		if (FreeImage_Save(FIF_JPEG, bitmap, "output.jpeg", 0))
		{
			std::cout << "Bitmap successfully saved!" << std::endl;

			FreeImage_Unload(bitmap);
		}
	}
}}
