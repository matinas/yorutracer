#include <iostream>

#include <FreeImage.h>

#include <glm/ext.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "yoru/utils.h"

using namespace std;
using namespace yorutracer;

glm::vec3 canvas_to_viewport(const glm::vec2, const glm::vec2, const glm::vec2, float);
glm::vec2 canvas_to_screen_glm(const glm::vec2, const glm::vec2);
glm::vec2 canvas_to_screen_custom(const glm::vec2, const glm::vec2);

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

	glm::vec2 pixel(-960,540);
	glm::vec3 v_coords = canvas_to_viewport(pixel, glm::vec2(1920,1080), glm::vec2(1,1), 1);

	cout << "Canvas coordinates: (" << pixel.x << ", " << pixel.y << ")" << endl;
	cout << "Viewport coordinates: (" << v_coords.x << ", " << v_coords.y << ", " << v_coords.z << ")" << endl;

	glm::vec2 s_coords = canvas_to_screen_glm(pixel, glm::vec2(1920,1080));
	cout << "Screen coordinates: (" << s_coords.x << ", " << s_coords.y << ")" << endl;

	return 0;
}

glm::vec3 canvas_to_viewport(const glm::vec2 canvas_coord, const glm::vec2 canvas_size, const glm::vec2 viewport_size, float d)
{
	glm::mat2x2 scale_matrix(viewport_size.x / canvas_size.x, 0.0f,   // ( Vw/Cw   0   )
							 0.0f, viewport_size.y / canvas_size.y);  // (   0   Vh/Ch )

	glm::vec3 viewport_coord = glm::vec3(scale_matrix * canvas_coord, d);

	return viewport_coord;
}

glm::vec2 canvas_to_screen_glm(const glm::vec2 canvas_coord, const glm::vec2 canvas_size)
{
	// note: we transpose the scale and translate matrices as we are defining them in column-major form (so we use post-multiplication to apply them: T * S * P).
	// in other words, we need the matrix-point multiplication to be done per-row: P'0 = 1st matrix row * P0, P'1 = 2nd matrix row * P1, etc
	// but glm handles matrices per-column, so if not transposed, matrix-point product would result in: P'0 = 1st matrix column * P0, P'1 = 2nd matrix column * P1
	// which will give us the wrong result when using post-multiplication (applying transforms from right (first) to left (last))
	// if we would want to avoid transposing, we could just pre-multiply and we should get the same result (do P * S * T, instead of T * S * P)

	glm::mat3x3 scale_matrix = glm::transpose(glm::mat3x3(1.0f, 0.0f, 0.0f,   // ( 1  0  0 )
														  0.0f, -1.0f, 0.0f,  // ( 0 -1  0 ) --> y-axis mirroring matrix
														  0.0f, 0.0f, 1.0f)); // ( 0  0  1 )

	glm::mat3x3 translate_matrix = glm::transpose(glm::mat3x3(1.0f, 0.0f, canvas_size.x/2,    // ( 1 0 Cw/2 )
															  0.0f, 1.0f, canvas_size.y/2,    // ( 0 1 Ch/2 ) --> translate origin matrix
															  0.0f, 0.0f,       1.0f	  )); // ( 0 0   1  )

	glm::vec3 new_canvas_coords = translate_matrix * scale_matrix * glm::vec3(canvas_coord, 1.0f); // T * S * Canvas_Pixel

	return glm::vec2(new_canvas_coords.x, new_canvas_coords.y);
}

glm::vec2 canvas_to_screen_custom(const glm::vec2 canvas_coord, const glm::vec2 canvas_size)
{
	float* scale_matrix;
	create_matrix_3x3(1.0f, 0.0f, 0.0f,  // ( 1  0  0 )
					  0.0f, -1.0f, 0.0f, // ( 0 -1  0 ) --> y-axis mirroring matrix
					  0.0f, 0.0f, 1.0f,  // ( 0  0  1 )
					  scale_matrix);

	float* translate_matrix;
	create_matrix_3x3(1.0f, 0.0f, canvas_size.x/2, // ( 1 0 Cw/2 )
					  0.0f, 1.0f, canvas_size.y/2, // ( 0 1 Ch/2 ) --> translate origin matrix
					  0.0f, 0.0f,       1.0f	 , // ( 0 0   1  )
					  translate_matrix);

	// as we are using traditional column-vector convention, we need to
	// post-multiply matrices/vectors (rightmost is the 1st applied transform)

	float* transform; 
	multiply_mat_3x3(translate_matrix, scale_matrix, transform); // T * S

	glm::vec3 new_canvas_coords;
	multiply_vec_3x3(transform, glm::vec3(canvas_coord, 1.0f), new_canvas_coords); // (T * S) * Canvas_Pixel (post-multiply vector as well)

	delete scale_matrix;
	delete translate_matrix;
	delete transform;

	return glm::vec2(new_canvas_coords.x, new_canvas_coords.y);
}