#ifndef UTILS_H
#define UTILS_H

#define MATRIX_3x3_SIZE 9

#include <sstream>

using namespace std;

namespace yorutracer {

void create_matrix_3x3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22, float* &mat)
{
	mat = new float[MATRIX_3x3_SIZE];

	mat[0] = m00; mat[1] = m01; mat[2] = m02;
	mat[3] = m10; mat[4] = m11; mat[5] = m12;
	mat[6] = m20; mat[7] = m21; mat[8] = m22;
}

void multiply_mat_3x3(const float* const lmat, const float* const rmat, float* &mult_mat)
{
	mult_mat = new float[MATRIX_3x3_SIZE];
	
	// multiply elements in the conventional way, as always (rows of the first matrix by columns on the second matrix)
	// the only thing we need to take into account is that we chose to store elems in row-major order by convention
	// so we need to pick the appropriate indexes for each term

	// product's 1st row
	mult_mat[0] = lmat[0]*rmat[0] + lmat[1]*rmat[3] + lmat[2]*rmat[6];
	mult_mat[1] = lmat[0]*rmat[1] + lmat[1]*rmat[4] + lmat[2]*rmat[7];
	mult_mat[2] = lmat[0]*rmat[2] + lmat[1]*rmat[5] + lmat[2]*rmat[8];

	// product's 2nd row
	mult_mat[3] = lmat[3]*rmat[0] + lmat[4]*rmat[3] + lmat[5]*rmat[6];
	mult_mat[4] = lmat[3]*rmat[1] + lmat[4]*rmat[4] + lmat[5]*rmat[7];
	mult_mat[5] = lmat[3]*rmat[2] + lmat[4]*rmat[5] + lmat[5]*rmat[8];

	// product's 3rd row
	mult_mat[6] = lmat[6]*rmat[0] + lmat[7]*rmat[3] + lmat[8]*rmat[6];
	mult_mat[7] = lmat[6]*rmat[1] + lmat[7]*rmat[4] + lmat[8]*rmat[7];
	mult_mat[8] = lmat[6]*rmat[2] + lmat[7]*rmat[5] + lmat[8]*rmat[8];
}

void multiply_vec_3x3(const float* const mat, const glm::vec3 vec, glm::vec3 &prod_mv)
{
	// as we are using column-vector convention for the matrices, we must post-multiply with vector (M*v)
	// once again, we just stick with the convention we chose

	prod_mv = glm::vec3(mat[0]*vec.x + mat[1]*vec.y + mat[2]*vec.z,
						mat[3]*vec.x + mat[4]*vec.y + mat[5]*vec.z,
						mat[6]*vec.x + mat[7]*vec.y + mat[8]*vec.z);
}

void get_addr_str(string** &addr_str_array, const glm::mat3x3 mat, bool print_address);
void free_addr_str(string** &m_addr, int length);

// prints the matrix in either column-major or row-major form,
// considering glm uses column-major ordering
void print_matrix_3x3(const glm::mat3x3 &mat, bool column_major, bool print_address)
{
	string** m_addr = NULL;
	get_addr_str(m_addr, mat, print_address);

	if (column_major)
	{
		cout << m_addr[0][0] << mat[0][0] << " " << m_addr[1][0] << mat[1][0] << " " << m_addr[2][0] << mat[2][0] << endl;
		cout << m_addr[0][1] << mat[0][1] << " " << m_addr[1][1] << mat[1][1] << " " << m_addr[2][1] << mat[2][1] << endl;
		cout << m_addr[0][2] << mat[0][2] << " " << m_addr[1][2] << mat[1][2] << " " << m_addr[2][2] << mat[2][2] << endl;
	}
	else
	{
		cout << m_addr[0][0] << mat[0][0] << " " << m_addr[0][1] << mat[0][1] << " " << m_addr[0][2] << mat[0][2] << endl;
		cout << m_addr[1][0] << mat[1][0] << " " << m_addr[1][1] << mat[1][1] << " " << m_addr[1][2] << mat[1][2] << endl;
		cout << m_addr[2][0] << mat[2][0] << " " << m_addr[2][1] << mat[2][1] << " " << m_addr[2][2] << mat[2][2] << endl;
	}

	free_addr_str(m_addr, mat.length());
}

void print_matrix_2x2(const glm::mat2x2 &mat, bool column_major)
{
	if (column_major)
	{
		cout << &mat[0][0] << ":" << mat[0][0] << " " << &mat[1][0] << ":" << mat[1][0] << endl;
		cout << &mat[0][1] << ":" << mat[0][1] << " " << &mat[1][0] << ":" << mat[1][1] << endl;
	}
	else
	{
		cout << &mat[0][0] << ":" << mat[0][0] << " " << &mat[0][1] << ":" << mat[0][1] << endl;
		cout << &mat[1][0] << ":" << mat[1][0] << " " << &mat[1][1] << ":" << mat[1][1] << endl;
	}
}

void get_addr_str(string** &addr_str_array, const glm::mat3x3 mat, bool print_address)
{
	int length = mat.length();

	if (addr_str_array == NULL)
	{
		addr_str_array = new string*[length];
		for (int i=0; i<length; ++i)
		{
			addr_str_array[i] = new string[length];
		}
	}

	for (int i=0; i<length; ++i)
	{
		for (int j=0; j<length; ++j)
		{
			stringstream ss;
			ss << std::hex << &mat[i][j];
			const std::string addr_str = ss.str();

			addr_str_array[i][j] = print_address ? addr_str + ":" : "";
		}
	}
}

void free_addr_str(string** &m_addr, int length)
{
	for (int i=0; i<length; ++i)
	{
		delete[] m_addr[i];
	}

	delete[] m_addr;
}

void glm_major_convention_tests()
{
	glm::mat2x2 m2 = glm::mat2x2(1.0f, 2.0f,
								 3.0f, 4.0f);

	glm::mat2x2 m2_trans = glm::transpose(m2);

	glm::vec2 p1(1,1);
	glm::vec2 v = m2 * p1;

	cout << "(" << v.x << "," << v.y << ")" << endl;

	glm::mat2x2 m3(10,20,
				   30,40);

	print_matrix_2x2(m2, false);
	print_matrix_2x2(m3, false);

	glm::mat2x2 mul = m2 * m3;

	print_matrix_2x2(mul, false);
}

}

#endif