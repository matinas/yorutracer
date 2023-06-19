#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <FreeImage.h>

#include "renderer\canvas.h"
#include "renderer\screen.h"
#include "renderer\camera.h"

namespace yoru {
namespace renderer {

	class Raytracer
	{
	public:
		Raytracer(const Canvas& canvas, const Screen& scree, const Camera& camera);
		~Raytracer();

		void render();
	private:
		Canvas canvas;
		Screen screen;
		Camera camera;
		FIBITMAP *bitmap;
	};
}}

#endif
