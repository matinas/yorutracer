#include <iostream>
#include <sstream>
#include <glm\glm.hpp>

#include "utils.h"

namespace yoru {
namespace utils {

	glm::vec3 canvas_to_viewport(const glm::vec2 canvas_coord, const glm::vec2 canvas_size, const glm::vec2 viewport_size, float d)
	{
		glm::mat2x2 scale_matrix(viewport_size.x / canvas_size.x, 0.0f,   // ( Vw/Cw   0   )
								 0.0f, viewport_size.y / canvas_size.y);  // (   0   Vh/Ch )

		glm::vec3 viewport_coord = glm::vec3(scale_matrix * canvas_coord, d);

		return viewport_coord;
	}

	glm::vec2 canvas_to_screen_glm(const glm::vec2 canvas_coord, const glm::vec2 canvas_size)
	{
		// note: we transpose the scale and translate matrices as we are actually defining them in column-vector form (so we use post-multiplication to apply them: T * S * P).
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

	// an alternative custom version that avoids using glm library for storing and handling matrices. the goal is just to prove
	// that we can get the same results even when we use a different vector and storage convention (column-vector matrices,
	// row-major storage, in contrast to the conventions used by glm which are row-vector matrices, column-major storage)
	// as long as we stay consistent with the chosen conventions, we should get the same results
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

	void create_matrix_3x3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22, float* &mat)
	{
		mat = new float[MATRIX_3x3_SIZE];

		mat[0] = m00; mat[1] = m01; mat[2] = m02; // store elements in a row-major storage layout, just by choice/convention
		mat[3] = m10; mat[4] = m11; mat[5] = m12;
		mat[6] = m20; mat[7] = m21; mat[8] = m22;

		// if we would've decided to store elements in a column-major storage layout...
		// mat[0] = m00; mat[3] = m01; mat[6] = m02;
		// mat[1] = m10; mat[4] = m11; mat[7] = m12;
		// mat[2] = m20; mat[5] = m21; mat[8] = m22;

		// float mat1[MATRIX_3x3_ROW_SIZE][MATRIX_3x3_ROW_SIZE]; // pretty much the same as above as a bidimensional array (row-major allocation)
		// mat1[0][0] = m00; mat1[0][1] = m01; mat1[0][2] = m02;
		// mat1[1][0] = m10; mat1[1][1] = m11; mat1[1][2] = m12;
		// mat1[2][0] = m20; mat1[2][1] = m21; mat1[2][2] = m22;
	}

	// get element (i,j) of the matrix mat considering it's stored in row-major order
	float get_elem_rm(const float* mat, int i, int j)
	{
		return mat[i*MATRIX_3x3_ROW_SIZE + j];

		// if we would've decided to store elements in a column-major storage layout...
		// return mat[j*MATRIX_3x3_ROW_SIZE + i];
	}

	void multiply_mat_3x3(const float* const lmat, const float* const rmat, float* &mult_mat)
	{
		mult_mat = new float[MATRIX_3x3_SIZE];
	
		// multiply elements in the conventional way, as always (dot product between rows of the first matrix with columns on the second matrix)
		// the only thing we need to take into account is that we chose to store elems in row-major order by convention
		// so we need to pick the appropriate indexes for each term. we encapsulated this behavior inside get_elem_rm(i,j)

		float lm00 = get_elem_rm(lmat,0,0), lm01 = get_elem_rm(lmat,0,1), lm02 = get_elem_rm(lmat,0,2),
			  lm10 = get_elem_rm(lmat,1,0), lm11 = get_elem_rm(lmat,1,1), lm12 = get_elem_rm(lmat,1,2),
			  lm20 = get_elem_rm(lmat,2,0), lm21 = get_elem_rm(lmat,2,1), lm22 = get_elem_rm(lmat,2,2);

		float rm00 = get_elem_rm(rmat,0,0), rm01 = get_elem_rm(rmat,0,1), rm02 = get_elem_rm(rmat,0,2),
			  rm10 = get_elem_rm(rmat,1,0), rm11 = get_elem_rm(rmat,1,1), rm12 = get_elem_rm(rmat,1,2),
			  rm20 = get_elem_rm(rmat,2,0), rm21 = get_elem_rm(rmat,2,1), rm22 = get_elem_rm(rmat,2,2);

		// product's 1st row
		mult_mat[0] = lm00*rm00 + lm01*rm10 + lm02*rm20;
		mult_mat[1] = lm00*rm01 + lm01*rm11 + lm02*rm21;
		mult_mat[2] = lm00*rm02 + lm01*rm12 + lm02*rm22;

		// product's 2nd row
		mult_mat[3] = lm10*rm00 + lm11*rm10 + lm12*rm20;
		mult_mat[4] = lm10*rm01 + lm11*rm11 + lm12*rm21;
		mult_mat[5] = lm10*rm02 + lm11*rm12 + lm12*rm22;

		// product's 3rd row
		mult_mat[6] = lm20*rm00 + lm21*rm10 + lm22*rm20;
		mult_mat[7] = lm20*rm01 + lm21*rm11 + lm22*rm21;
		mult_mat[8] = lm20*rm02 + lm21*rm12 + lm22*rm22;
	}

	void multiply_vec_3x3(const float* const mat, const glm::vec3 vec, glm::vec3 &prod_mv)
	{
		// as we are using column-vector convention for the matrices, we must post-multiply with vector (M*v)
		// once again, we just stick with the convention we chose

		prod_mv = glm::vec3(mat[0]*vec.x + mat[1]*vec.y + mat[2]*vec.z,
							mat[3]*vec.x + mat[4]*vec.y + mat[5]*vec.z,
							mat[6]*vec.x + mat[7]*vec.y + mat[8]*vec.z);
	}

	void get_addr_str(std::string** &addr_str_array, const glm::mat3x3 mat, bool print_address);
	void free_addr_str(std::string** &m_addr, int length);

	// prints the matrix in either column-major or row-major form,
	// considering glm uses column-major ordering
	void print_matrix_3x3(const glm::mat3x3 &mat, bool column_major, bool print_address)
	{
		std::string** m_addr = NULL;
		get_addr_str(m_addr, mat, print_address);

		if (column_major)
		{
			std::cout << m_addr[0][0] << mat[0][0] << " " << m_addr[1][0] << mat[1][0] << " " << m_addr[2][0] << mat[2][0] << std::endl;
			std::cout << m_addr[0][1] << mat[0][1] << " " << m_addr[1][1] << mat[1][1] << " " << m_addr[2][1] << mat[2][1] << std::endl;
			std::cout << m_addr[0][2] << mat[0][2] << " " << m_addr[1][2] << mat[1][2] << " " << m_addr[2][2] << mat[2][2] << std::endl;
		}
		else
		{
			std::cout << m_addr[0][0] << mat[0][0] << " " << m_addr[0][1] << mat[0][1] << " " << m_addr[0][2] << mat[0][2] << std::endl;
			std::cout << m_addr[1][0] << mat[1][0] << " " << m_addr[1][1] << mat[1][1] << " " << m_addr[1][2] << mat[1][2] << std::endl;
			std::cout << m_addr[2][0] << mat[2][0] << " " << m_addr[2][1] << mat[2][1] << " " << m_addr[2][2] << mat[2][2] << std::endl;
		}

		free_addr_str(m_addr, mat.length());
	}

	void print_matrix_2x2(const glm::mat2x2 &mat, bool column_major)
	{
		if (column_major)
		{
			std::cout << &mat[0][0] << ":" << mat[0][0] << " " << &mat[1][0] << ":" << mat[1][0] << std::endl;
			std::cout << &mat[0][1] << ":" << mat[0][1] << " " << &mat[1][0] << ":" << mat[1][1] << std::endl;
		}
		else
		{
			std::cout << &mat[0][0] << ":" << mat[0][0] << " " << &mat[0][1] << ":" << mat[0][1] << std::endl;
			std::cout << &mat[1][0] << ":" << mat[1][0] << " " << &mat[1][1] << ":" << mat[1][1] << std::endl;
		}
	}

	void get_addr_str(std::string** &addr_str_array, const glm::mat3x3 mat, bool print_address)
	{
		int length = mat.length();

		if (addr_str_array == NULL)
		{
			addr_str_array = new std::string*[length];
			for (int i=0; i<length; ++i)
			{
				addr_str_array[i] = new std::string[length];
			}
		}

		for (int i=0; i<length; ++i)
		{
			for (int j=0; j<length; ++j)
			{
				std::stringstream ss;
				ss << std::hex << &mat[i][j];
				const std::string addr_str = ss.str();

				addr_str_array[i][j] = print_address ? addr_str + ":" : "";
			}
		}
	}

	void free_addr_str(std::string** &m_addr, int length)
	{
		for (int i=0; i<length; ++i)
		{
			delete[] m_addr[i];
		}

		delete[] m_addr;
	}
}
}