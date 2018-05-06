#include "mat4.h"

mat4 mat4::createRotateX(const float& degrees) { // create a rotation matrix around the x axis
	mat4 m;
	float d = ((PI / 180) * degrees);
	m.m_elements[0][0] = 1;  m.m_elements[0][1] = 0; m.m_elements[0][2] = 0; m.m_elements[0][3] = 0;
	m.m_elements[1][0] = 0;  m.m_elements[1][1] = cos(d); m.m_elements[1][2] = -sin(d); m.m_elements[1][3] = 0;
	m.m_elements[2][0] = 0;  m.m_elements[2][1] = sin(d); m.m_elements[2][2] = cos(d); m.m_elements[2][3] = 0;
	m.m_elements[3][0] = 0;  m.m_elements[3][1] = 0; m.m_elements[3][2] = 0; m.m_elements[3][3] = 1;
	return m;
}
mat4 mat4::createRotateY(const float& degrees) { // create a rotation matrix around the y axis
	mat4 m;
	float d = ((PI / 180) * degrees);
	m.m_elements[0][0] = cos(d);  m.m_elements[0][1] = 0; m.m_elements[0][2] = sin(d); m.m_elements[0][3] = 0;
	m.m_elements[1][0] = 0;  m.m_elements[1][1] = 1; m.m_elements[1][2] = 0; m.m_elements[1][3] = 0;
	m.m_elements[2][0] = -sin(d);  m.m_elements[2][1] = 0; m.m_elements[2][2] = cos(d); m.m_elements[2][3] = 0;
	m.m_elements[3][0] = 0;  m.m_elements[3][1] = 0; m.m_elements[3][2] = 0; m.m_elements[3][3] = 1;
	return m;
}
mat4 mat4::createRotateZ(const float& degrees) { // create a rotation matrix around the z axis
	mat4 m;
	float d = ((PI / 180) * degrees);
	m.m_elements[0][0] = cos(d);  m.m_elements[0][1] = -sin(d); m.m_elements[0][2] = 0; m.m_elements[0][3] = 0;
	m.m_elements[1][0] = sin(d);  m.m_elements[1][1] = cos(d); m.m_elements[1][2] = 0; m.m_elements[1][3] = 0;
	m.m_elements[2][0] = 0;  m.m_elements[2][1] = 0; m.m_elements[2][2] = 1; m.m_elements[2][3] = 0;
	m.m_elements[3][0] = 0;  m.m_elements[3][1] = 0; m.m_elements[3][2] = 0; m.m_elements[3][3] = 1;
	return m;
}

mat4 mat4::createRotationMat(const float& degreesX, const float& degreesY, const float& degreesZ) { // create a rotation matrix
	mat4 m;
	m = createRotateX(degreesX) * createRotateY(degreesY) * createRotateZ(degreesZ);
	return m;
}


mat4 mat4::createTranslationMat(const float& Tx, const float& Ty, const float& Tz) { // creates a translation matrix
	mat4 m;
	m.m_elements[0][0] = 1;  m.m_elements[0][1] = 0; m.m_elements[0][2] = 0; m.m_elements[0][3] = 0;
	m.m_elements[1][0] = 0;  m.m_elements[1][1] = 1; m.m_elements[1][2] = 0; m.m_elements[1][3] = 0;
	m.m_elements[2][0] = 0;  m.m_elements[2][1] = 0; m.m_elements[2][2] = 1; m.m_elements[2][3] = 0;
	m.m_elements[3][0] = Tx;  m.m_elements[3][1] = Ty; m.m_elements[3][2] = Tz; m.m_elements[3][3] = 1;
	return m;
}

mat4 mat4::createTranslationMat(const vec4& v) { // creates a translation matrix
	mat4 m;
	m.m_elements[0][0] = 1;  m.m_elements[0][1] = 0; m.m_elements[0][2] = 0; m.m_elements[0][3] = 0;
	m.m_elements[1][0] = 0;  m.m_elements[1][1] = 1; m.m_elements[1][2] = 0; m.m_elements[1][3] = 0;
	m.m_elements[2][0] = 0;  m.m_elements[2][1] = 0; m.m_elements[2][2] = 1; m.m_elements[2][3] = 0;
	m.m_elements[3][0] = v.elts[0];  m.m_elements[3][1] = v.elts[1]; m.m_elements[3][2] = v.elts[2]; m.m_elements[3][3] = 1;
	return m;
}

//This section is for the inverse of a matrix (4v4).  
//This was taken from https://www.geeksforgeeks.org/adjoint-inverse-matrix/.
//Modified to work for my code with mat4 objects
mat4 mat4::getCofactor(mat4 A, int p, int q, int n)
{
	int i = 0, j = 0;
	mat4 temp;

	// Looping for each element of the matrix
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			//  Copying into temporary matrix only those element
			//  which are not in given row and column
			if (row != p && col != q)
			{
				temp.m_elements[i][j++] = A.m_elements[row][col];

				// Row is filled, so increase row index and
				// reset col index
				if (j == n - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}

	return temp;
}

float mat4::determinant(mat4 A, int n)
{
	float D = 0; // Initialize result

				 //  Base case : if matrix contains single element
	if (n == 1)
		return A.m_elements[0][0];

	mat4 temp; // To store cofactors

	int sign = 1;  // To store sign multiplier

				   // Iterate for each element of first row
	for (int f = 0; f < n; f++)
	{
		// Getting Cofactor of A[0][f]
		temp = getCofactor(A, 0, f, n);
		D += sign * A.m_elements[0][f] * determinant(temp, n - 1);

		// terms are to be added with alternate sign
		sign = -sign;
	}

	return D;
}

mat4 mat4::adjoint(mat4 A)
{
	// temp is used to store cofactors of A
	int sign = 1;
	mat4 temp;
	mat4 adj;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			// Get cofactor of A[i][j]
			temp = getCofactor(A, i, j, 4);

			// sign of adj[j][i] positive if sum of row
			// and column indexes is even.
			sign = ((i + j) % 2 == 0) ? 1 : -1;

			// Interchanging rows and columns to get the
			// transpose of the cofactor matrix
			adj.m_elements[j][i] = (sign)*(determinant(temp, 4 - 1));
			if (adj.m_elements[j][i] == -0) {
				adj.m_elements[j][i] = 0;
			}
		}
	}
	return adj;
}

mat4 mat4::inverse(mat4 A) // returns the inverse of a matrix
{

	mat4 inverse;
	// Find determinant of A
	float det = determinant(A, 4);
	if (det == 0)
	{
		return inverse;
	}

	// Find adjoint
	mat4 adj;
	adj = adjoint(A);


	// Find Inverse using formula "inverse(A) = adj(A)/det(A)"
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			inverse.m_elements[i][j] = adj.m_elements[i][j] / float(det);

	return inverse;
}

vec4 mat4::mulVectorMatrix(const vec4& v, const mat4& a) // multiply a vector by a matrix
{
#define SHUFFLE_PARAM(x,y,z,w)\
	((x) | ((y) << 2 | ((z) << 4) | ((w) << 6)))
#define _mm_replicate_x_ps(v)\
	_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(0, 0, 0, 0))
#define _mm_replicate_y_ps(v)\
	_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(1, 1, 1, 1))
#define _mm_replicate_z_ps(v)\
	_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(2, 2, 2, 2))
#define _mm_replicate_w_ps(v)\
	_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(3, 3, 3, 3))
#define _mm_madd_ps(a,b,c)\
	_mm_add_ps(_mm_mul_ps((a), (b)), (c))

	__m128 temp;
	__m128 aRow0 = _mm_loadu_ps(a.m_elements[0]);
	__m128 aRow1 = _mm_loadu_ps(a.m_elements[1]);
	__m128 aRow2 = _mm_loadu_ps(a.m_elements[2]);
	__m128 aRow3 = _mm_loadu_ps(a.m_elements[3]);
	__m128 vec = _mm_loadu_ps(v.elts);
	temp = _mm_mul_ps(_mm_replicate_x_ps(vec), aRow0);
	temp = _mm_madd_ps(_mm_replicate_y_ps(vec), aRow1, temp);
	temp = _mm_madd_ps(_mm_replicate_z_ps(vec), aRow2, temp);
	temp = _mm_madd_ps(_mm_replicate_w_ps(vec), aRow3, temp);
	vec4 result;
	_mm_storeu_ps(result.elts, temp);
	return result;
}
