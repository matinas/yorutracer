#ifndef UTILS_H
#define UTILS_H

#include <sstream>

using namespace std;

namespace yorutracer {

void generate_addr_str(string** *addr_str_array, const glm::mat3x3 mat, bool print_address)
{
	int length = mat.length();

	if (*addr_str_array == NULL)
	{
		*addr_str_array = new string*[length];
		for (int i=0; i<length; ++i)
		{
			(*addr_str_array)[i] = new string[length];
		}
	}

	for (int i=0; i<length; ++i)
	{
		for (int j=0; j<length; ++j)
		{
			stringstream ss;
			ss << std::hex << &mat[i][j];
			const std::string addr_str = ss.str();

			(*addr_str_array)[i][j] = print_address ? ":" + addr_str : "";
		}
	}
}

void free_addr_str(string** *m_addr, int length)
{
	for (int i=0; i<length; ++i)
	{
		delete[] (*m_addr)[i];
	}

	delete[] (*m_addr);
}

// prints the matrix in either column-major or row-major form,
// considering glm uses column-major ordering
void print_matrix(const glm::mat3x3 mat, bool column_major, bool print_address)
{
	string** m_addr = NULL;
	generate_addr_str(&m_addr, mat, print_address);

	if (column_major)
	{
		cout << mat[0][0] << m_addr[0][0] << " " << mat[1][0] << m_addr[1][0]  << " " << mat[2][0] << m_addr[2][0] << endl;
		cout << mat[0][1] << m_addr[0][1]  << " " << mat[1][1] << m_addr[1][1]  << " " << mat[2][1] << m_addr[2][1]  << endl;
		cout << mat[0][2] << m_addr[0][2]  << " " << mat[1][2] << m_addr[1][2]  << " " << mat[2][2]  << m_addr[2][2] << endl;
	}
	else
	{
		cout << mat[0][0] << m_addr[0][0] << " " << mat[0][1] << m_addr[0][1] << " " << mat[0][2] << m_addr[0][0] << endl;
		cout << mat[1][0] << m_addr[1][0] << " " << mat[1][1] << m_addr[1][1] << " " << mat[1][2] << m_addr[1][2] << endl;
		cout << mat[2][0] << m_addr[2][0] << " " << mat[2][1] << m_addr[2][1] << " " << mat[2][2] << m_addr[2][2] << endl;
	}

	free_addr_str(&m_addr, mat.length());
}

}

#endif