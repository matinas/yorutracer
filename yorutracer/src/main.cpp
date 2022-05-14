#include <iostream>

#include <FreeImage.h>

#include <glm/ext.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat2x2.hpp>

#include "utils.h"

using namespace std;
using namespace yorutracer;

glm::vec3 canvas_to_viewport(const glm::vec2, const glm::vec2, const glm::vec2, float);
glm::vec2 canvas_to_screen(const glm::vec2, const glm::vec2);

int main()
{
	FreeImage_Initialise();

	FIBITMAP *bitmap = FreeImage_Allocate(320, 240, 32);

	if (FreeImage_Save(FIF_JPEG, bitmap, "mybitmap.jpeg", 0))
	{
		cout << "Bitmap successfully saved!" << endl;
	}

	if (bitmap)
	{
		FreeImage_Unload(bitmap);
	}

	glm::vec2 pix(-960,540);
	glm::vec3 v_coords = canvas_to_viewport(pix, glm::vec2(1920,1080), glm::vec2(1,1), 1);

	glm::mat3x3 m1 = glm::mat3x3(0.0f, 0.1f, 0.2f,
								 1.0f, 1.1f, 1.2f,
								 2.0f, 2.1f, 2.2f);

	print_matrix(m1, false, true);

	cout << "Canvas coordinates: (" << pix.x << ", " << pix.y << ")" << endl;
	cout << "Viewport coordinates: (" << v_coords.x << ", " << v_coords.y << ", " << v_coords.z << ")" << endl;

	glm::vec2 s_coords = canvas_to_screen(pix, glm::vec2(1920,1080));
	cout << "Screen coordinates: (" << s_coords.x << ", " << s_coords.y << ")" << endl;

	return 0;
}

glm::vec2 canvas_to_screen(const glm::vec2 canvas_coord, const glm::vec2 canvas_size)
{
	// note: we transpose the matrices as we are already defining the scale and translate matrices in column-major
	// form but as glm uses column-major memory ordering it will use them transposed otherwise. and we want to operate
	// in the column-major form (apply transforms from right (first) to left (last), etc), thus the transpose

	glm::mat3x3 scale_matrix = glm::transpose(glm::mat3x3(1.0f, 0.0f, 0.0f,   // ( 1  0  0 )
														  0.0f, -1.0f, 0.0f,  // ( 0 -1  0 ) --> y-axis mirroring matrix
														  0.0f, 0.0f, 1.0f)); // ( 0  0  1 )

	glm::mat3x3 translate_matrix = glm::transpose(glm::mat3x3(1.0f, 0.0f, canvas_size.x/2,    // ( 1 0 Cw/2 )
															  0.0f, 1.0f, canvas_size.y/2,    // ( 0 1 Ch/2 ) --> translate origin matrix
															  0.0f, 0.0f,       1.0f	  )); // ( 0 0   1  )

	glm::mat3x3 canvas_to_screen_transform = translate_matrix * scale_matrix; // T * S

	print_matrix(canvas_to_screen_transform, true, true);

	glm::vec3 new_canvas_coords = canvas_to_screen_transform * glm::vec3(canvas_coord, 1.0f); // T * S * Canvas_Pixel

	return glm::vec2(new_canvas_coords.x, new_canvas_coords.y);
}

glm::vec3 canvas_to_viewport(const glm::vec2 canvas_coord, const glm::vec2 canvas_size, const glm::vec2 viewport_size, float d)
{
	glm::mat2x2 scale_matrix(viewport_size.x / canvas_size.x, 0.0f,   // ( Vw/Cw   0   )
							 0.0f, viewport_size.y / canvas_size.y);  // (   0   Vh/Ch )

	glm::vec3 viewport_coord = glm::vec3(scale_matrix * canvas_coord, d);

	return viewport_coord;
}