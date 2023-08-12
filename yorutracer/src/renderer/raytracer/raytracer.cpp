#include <iostream>
#include <vector>

#include "renderer\raytracer\raytracer.h"
#include "renderer\raytracer\ray.h"
#include "renderer\raytracer\rayintersectioninfo.h"

#include "objects\sphere.h"
#include "utils\utils.h"

RGBQUAD rgbBlack = {0,0,0};
RGBQUAD rgbBlue = {255,0,0};
RGBQUAD rgbRed = {0,0,255};

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
		objects::Sphere blueSphere = objects::Sphere(yorumathpoint::Point3f(0.0f,0.0f,3.0f), 1.0f, yorumathpoint::Point3f(0.f,0.f,1.0f));
		objects::Sphere redSphere2 = objects::Sphere(yorumathpoint::Point3f(1.f,0.f,4.5f), 1.5f, yorumathpoint::Point3f(1.f,0.f,0.0f));
		
		std::vector<objects::Sphere> spheres = std::vector<objects::Sphere>();

		spheres.push_back(blueSphere);
		spheres.push_back(redSphere2);

		int width = canvas.getWidth();
		int height = canvas.getHeight();

		RGBQUAD rgb;
		for (int i=-width/2; i<width/2; ++i)
		{
			for (int j=-height/2; j<height/2; ++j)
			{
				yorumathpoint::Point3f viewportPoint = canvas.toViewportCoords(yorumathpoint::Point2i(i,j), camera);
				Ray ray = Ray(camera.getOrigin(), viewportPoint);

				for (unsigned obj=0; obj<spheres.size(); obj++) // TODO: we must go through all the objects in the scene here and keep the nearest hit
				{
					yoru:objects::Sphere sphere = spheres[obj];
					sphere.transform(camera.getViewMatrix()); // TODO: we still need to take into acount the camera position as part of this (right now we support only rotation)
					yorumathpoint::Point3f sphereColor = sphere.getColor();
					RGBQUAD sphereRGB = utils::toRGBQUAD(sphereColor);

					RayIntersectionInfo hitInfo = sphere.intersect(ray);
					
					if (hitInfo.hasHits())
					{
						yorumathpoint::Point3f* point = hitInfo.getNearest();
						rgb = camera.isInsideVolume(*point) ? sphereRGB : rgbBlack; // check whether the hit point is in front of the camera (don't render anything behind the camera)

						break;
					}
					else
					{
						rgb = rgbBlack;
					}
				}

				yorumathpoint::Point2i screenPoint = canvas.toScreenCoords(yorumathpoint::Point2i(i,j), screen);

				// we need to take into account that FreeImage coordinate system differs from the one we defined for the screen: origin at top-right, x goes right, y goes down
				// instead it uses a coordinate system where origin is at bottom-right, x goes right, y goes up, so we need to mirror the y (yes, once again)
				// from FreeImage doc: "FIBITMAP are based on a coordinate system that is upside down relative to usual graphics conventions. Thus, the scanlines are
				// stored upside down, with the first scan in memory being the bottom-most scan in the image
				FreeImage_SetPixelColor(bitmap, screenPoint.getX(), screen.getHeight() - screenPoint.getY(), &rgb);
			}
		}

		if (FreeImage_Save(FIF_JPEG, bitmap, "output.jpeg", 0))
		{
			std::cout << "Bitmap successfully saved!" << std::endl;

			FreeImage_Unload(bitmap);
			FreeImage_DeInitialise();
		}
	}
}}
