#include <iostream>
#include <sstream>

#include "utils.h"

namespace yorutracer {

void create_matrix_3x3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22, float* &mat)
{
	mat = new float[MATRIX_3x3_SIZE];

	mat[0] = m00; mat[1] = m01; mat[2] = m02; // store elements in a row-major storage layout, just by choice/convention
	mat[3] = m10; mat[4] = m11; mat[5] = m12;
	mat[6] = m20; mat[7] = m21; mat[8] = m22;
}

// get element (i,j) of the matrix mat considering it's stored in row-major order
float get_elem_rm(const float* mat, int i, int j)
{
	return mat[i*MATRIX_3x3_ROW_SIZE + j];
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