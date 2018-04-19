#include "mat4.h"

mat4::mat4() //constructor creates an identity matrix
{
	m_elements[0][0] = 1;  m_elements[0][1] = 0; m_elements[0][2] = 0; m_elements[0][3] = 0;
	m_elements[1][0] = 0;  m_elements[1][1] = 1; m_elements[1][2] = 0; m_elements[1][3] = 0;
	m_elements[2][0] = 0;  m_elements[2][1] = 0; m_elements[2][2] = 1; m_elements[2][3] = 0;
	m_elements[3][0] = 0;  m_elements[3][1] = 0; m_elements[3][2] = 0; m_elements[3][3] = 1;
}

mat4::mat4(float f) //constructor creates a scale matrix
{
	m_elements[0][0] = f;  m_elements[0][1] = 0; m_elements[0][2] = 0; m_elements[0][3] = 0;
	m_elements[1][0] = 0;  m_elements[1][1] = f; m_elements[1][2] = 0; m_elements[1][3] = 0;
	m_elements[2][0] = 0;  m_elements[2][1] = 0; m_elements[2][2] = f; m_elements[2][3] = 0;
	m_elements[3][0] = 0;  m_elements[3][1] = 0; m_elements[3][2] = 0; m_elements[3][3] = 1;
}

mat4::mat4(float fx, float fy, float fz) {
	m_elements[0][0] = fx;  m_elements[0][1] = 0; m_elements[0][2] = 0; m_elements[0][3] = 0;
	m_elements[1][0] = 0;  m_elements[1][1] = fy; m_elements[1][2] = 0; m_elements[1][3] = 0;
	m_elements[2][0] = 0;  m_elements[2][1] = 0; m_elements[2][2] = fz; m_elements[2][3] = 0;
	m_elements[3][0] = 0;  m_elements[3][1] = 0; m_elements[3][2] = 0; m_elements[3][3] = 1;
}

void mat4::getFloatValues(mat4 m, float f[]) {
	f[0]  = m.m_elements[0][0]; 	f[1]  = m.m_elements[0][1]; 	f[2]  = m.m_elements[0][2]; 	f[3]  = m.m_elements[0][3];
	f[4]  = m.m_elements[1][0]; 	f[5]  = m.m_elements[1][1]; 	f[6]  = m.m_elements[1][2]; 	f[7]  = m.m_elements[1][3];
	f[8]  = m.m_elements[2][0]; 	f[9]  = m.m_elements[2][1]; 	f[10] = m.m_elements[2][2]; 	f[11] = m.m_elements[2][3];
	f[12] = m.m_elements[3][0];		f[13] = m.m_elements[3][1]; 	f[14] = m.m_elements[3][2]; 	f[15] = m.m_elements[3][3];
}

void mat4::print(mat4 m) { // print the matrix
	std::cout << "the matrix is: " << std::endl;
	std::cout << m.m_elements[0][0] << " " << m.m_elements[0][1] << " " << m.m_elements[0][2] << " " << m.m_elements[0][3] << std::endl;
	std::cout << m.m_elements[1][0] << " " << m.m_elements[1][1] << " " << m.m_elements[1][2] << " " << m.m_elements[1][3] << std::endl;
	std::cout << m.m_elements[2][0] << " " << m.m_elements[2][1] << " " << m.m_elements[2][2] << " " << m.m_elements[2][3] << std::endl;
	std::cout << m.m_elements[3][0] << " " << m.m_elements[3][1] << " " << m.m_elements[3][2] << " " << m.m_elements[3][3] << std::endl;

}

void mat4::scale(mat4 *m, const float& f) { // change a matrix to a scale matrix
	m->m_elements[0][0] = m->m_elements[0][0] * f;
	m->m_elements[1][1] = m->m_elements[1][1] * f;
	m->m_elements[2][2] = m->m_elements[2][2] * f;
}

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

mat4 mat4::perspective(float fovy, float aspect, float n, float f) // create a persepctive view matrix
{
	float q = 1.0f / ((float) tan(0.5f * fovy));
	float A = q / aspect;
	float B = (n + f) / (n - f);
	float C = (2.0f * n * f) / (n - f);
	mat4 r = mat4();
	r.m_elements[0][0] = A;
	r.m_elements[1][1] = q;
	r.m_elements[2][2] = B;
	r.m_elements[2][3] = -1.0f;
	r.m_elements[3][2] = C;
	r.m_elements[3][3] = 0;
	return r;

}


mat4 mat4::ortho(float left, float right, float top, float bottom, float near, float far)
{
	mat4 m = mat4();

	m.m_elements[0][0] = 2.0f / (right - left);
	m.m_elements[0][1] = 0.0f;
	m.m_elements[0][2] = 0.0f;
	m.m_elements[0][3] = 0.0f;

	m.m_elements[1][0] = 0.0f;
	m.m_elements[1][1] = 2.0f / (top - bottom);
	m.m_elements[1][2] = 0.0f;
	m.m_elements[1][3] = 0.0f;

	m.m_elements[2][0] = 0.0f;
	m.m_elements[2][1] = 0.0f;
	m.m_elements[2][2] = -2.0f / (far - near);
	m.m_elements[2][3] = 0.0f;

	m.m_elements[3][0] = -(right + left) / (right - left);
	m.m_elements[3][1] = -(top + bottom) / (top - bottom);
	m.m_elements[3][2] = -(far + near) / (far - near);
	m.m_elements[3][3] = 1.0f;

	return m;
}

mat4 mat4::lookAt(vec4 eye, vec4 target, vec4 y)
{
	/*mat4 look = mat4();
	vec4 eyeV = vec4(eye);
	vec4 targetV = vec4(target);
	vec4 Fwd = vec4::normalize((targetV - eyeV));
	vec4 Right = vec4::normalize(vec4::cross(Fwd, y));
	vec4 Up = vec4::normalize(vec4::cross(Right, Fwd));

	look.m_elements[0][0] = Right.elts[0];
	look.m_elements[0][1] = Up.elts[0];
	look.m_elements[0][2] = -Fwd.elts[0];
	look.m_elements[0][3] = 0;
	look.m_elements[1][0] = Right.elts[1];
	look.m_elements[1][1] = Up.elts[1];
	look.m_elements[1][2] = -Fwd.elts[1];
	look.m_elements[1][3] = 0;
	look.m_elements[2][0] = Right.elts[2];
	look.m_elements[2][1] = Up.elts[2];
	look.m_elements[2][2] = -Fwd.elts[2];
	look.m_elements[2][3] = 0;
	look.m_elements[3][0] = vec4::dot(Right, (eyeV * -1));
	look.m_elements[3][1] = vec4::dot(Up, (eyeV * -1));
	look.m_elements[3][2] = vec4::dot((Fwd * -1), (eyeV * 1));
	look.m_elements[3][3] = 1.0f;
	return look;



	*/
	mat4 look;
	vec4 Y;

	//Fwd = eye - (this->Position + this->Fwd);
	//vec4::normalize(this->Fwd);
	vec4 Fwd = vec4::normalize((target - eye));
	Y = y;
	vec4 Right = vec4::cross(Y, Fwd);

	Y = vec4::cross(Fwd, Right);

	vec4::normalize(Right);
	vec4::normalize(Y);

	look.m_elements[0][0] = Right.elts[0];
	look.m_elements[1][0] = Right.elts[1];
	look.m_elements[2][0] = Right.elts[2];
	look.m_elements[3][0] = -vec4::dot(Right, eye);
	look.m_elements[0][1] = Y.elts[0];
	look.m_elements[1][1] = Y.elts[1];
	look.m_elements[2][1] = Y.elts[2];
	look.m_elements[3][1] = -vec4::dot(Y, eye);
	look.m_elements[0][2] = Fwd.elts[0];
	look.m_elements[1][2] = Fwd.elts[1];
	look.m_elements[2][2] = Fwd.elts[2];
	look.m_elements[3][2] = -vec4::dot(Fwd, eye);
	look.m_elements[0][3] = 0;
	look.m_elements[1][3] = 0;
	look.m_elements[2][3] = 0;
	look.m_elements[3][3] = 1.0f;

	return look;


}

mat4 mat4::transpose(const mat4& a) { // transpose a matrix

	mat4 transMat;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			transMat.m_elements[row][col] = a.m_elements[col][row];
		}
	}
	__m128 transRow0 = _mm_loadu_ps(transMat.m_elements[0]);
	__m128 transRow1 = _mm_loadu_ps(transMat.m_elements[1]);
	__m128 transRow2 = _mm_loadu_ps(transMat.m_elements[2]);
	__m128 transRow3 = _mm_loadu_ps(transMat.m_elements[3]);

	return transMat;
}

inline mat4 operator+(const mat4& a, const mat4& b)
{
	mat4 result;

	__m128 otherRow0 = _mm_load_ps(b.m_elements[0]);
	__m128 otherRow1 = _mm_load_ps(b.m_elements[1]);
	__m128 otherRow2 = _mm_load_ps(b.m_elements[2]);
	__m128 otherRow3 = _mm_load_ps(b.m_elements[3]);
	__m128 Row0 = _mm_load_ps(a.m_elements[0]);
	__m128 Row1 = _mm_load_ps(a.m_elements[1]);
	__m128 Row2 = _mm_load_ps(a.m_elements[2]);
	__m128 Row3 = _mm_load_ps(a.m_elements[3]);

	__m128 newRow0 = _mm_add_ps(otherRow0, Row0);
	__m128 newRow1 = _mm_add_ps(otherRow1, Row1);
	__m128 newRow2 = _mm_add_ps(otherRow2, Row2);
	__m128 newRow3 = _mm_add_ps(otherRow3, Row3);

	_mm_store_ps(result.m_elements[0], newRow0);
	_mm_store_ps(result.m_elements[1], newRow1);
	_mm_store_ps(result.m_elements[2], newRow2);
	_mm_store_ps(result.m_elements[3], newRow3);

	return result;
}

inline mat4 operator-(const mat4& a, const mat4& b)
{
	mat4 result;

	__m128 otherRow0 = _mm_load_ps(b.m_elements[0]);
	__m128 otherRow1 = _mm_load_ps(b.m_elements[1]);
	__m128 otherRow2 = _mm_load_ps(b.m_elements[2]);
	__m128 otherRow3 = _mm_load_ps(b.m_elements[3]);
	__m128 Row0 = _mm_load_ps(a.m_elements[0]);
	__m128 Row1 = _mm_load_ps(a.m_elements[1]);
	__m128 Row2 = _mm_load_ps(a.m_elements[2]);
	__m128 Row3 = _mm_load_ps(a.m_elements[3]);

	__m128 newRow0 = _mm_sub_ps(otherRow0, Row0);
	__m128 newRow1 = _mm_sub_ps(otherRow1, Row1);
	__m128 newRow2 = _mm_sub_ps(otherRow2, Row2);
	__m128 newRow3 = _mm_sub_ps(otherRow3, Row3);

	_mm_store_ps(result.m_elements[0], newRow0);
	_mm_store_ps(result.m_elements[1], newRow1);
	_mm_store_ps(result.m_elements[2], newRow2);
	_mm_store_ps(result.m_elements[3], newRow3);

	return result;
}

inline mat4 operator*(const mat4& a, const mat4& b)
{

	mat4 result;

	__m128 otherRow0 = _mm_load_ps(b.m_elements[0]);
	__m128 otherRow1 = _mm_load_ps(b.m_elements[1]);
	__m128 otherRow2 = _mm_load_ps(b.m_elements[2]);
	__m128 otherRow3 = _mm_load_ps(b.m_elements[3]);

	__m128 newRow0 = _mm_mul_ps(otherRow0, _mm_set1_ps(a.m_elements[0][0]));
	newRow0 = _mm_add_ps(newRow0, _mm_mul_ps(otherRow1, _mm_set1_ps(a.m_elements[0][1])));
	newRow0 = _mm_add_ps(newRow0, _mm_mul_ps(otherRow2, _mm_set1_ps(a.m_elements[0][2])));
	newRow0 = _mm_add_ps(newRow0, _mm_mul_ps(otherRow3, _mm_set1_ps(a.m_elements[0][3])));

	__m128 newRow1 = _mm_mul_ps(otherRow0, _mm_set1_ps(a.m_elements[1][0]));
	newRow1 = _mm_add_ps(newRow1, _mm_mul_ps(otherRow1, _mm_set1_ps(a.m_elements[1][1])));
	newRow1 = _mm_add_ps(newRow1, _mm_mul_ps(otherRow2, _mm_set1_ps(a.m_elements[1][2])));
	newRow1 = _mm_add_ps(newRow1, _mm_mul_ps(otherRow3, _mm_set1_ps(a.m_elements[1][3])));

	__m128 newRow2 = _mm_mul_ps(otherRow0, _mm_set1_ps(a.m_elements[2][0]));
	newRow2 = _mm_add_ps(newRow2, _mm_mul_ps(otherRow1, _mm_set1_ps(a.m_elements[2][1])));
	newRow2 = _mm_add_ps(newRow2, _mm_mul_ps(otherRow2, _mm_set1_ps(a.m_elements[2][2])));
	newRow2 = _mm_add_ps(newRow2, _mm_mul_ps(otherRow3, _mm_set1_ps(a.m_elements[2][3])));

	__m128 newRow3 = _mm_mul_ps(otherRow0, _mm_set1_ps(a.m_elements[3][0]));
	newRow3 = _mm_add_ps(newRow3, _mm_mul_ps(otherRow1, _mm_set1_ps(a.m_elements[3][1])));
	newRow3 = _mm_add_ps(newRow3, _mm_mul_ps(otherRow2, _mm_set1_ps(a.m_elements[3][2])));
	newRow3 = _mm_add_ps(newRow3, _mm_mul_ps(otherRow3, _mm_set1_ps(a.m_elements[3][3])));

	_mm_storeu_ps(result.m_elements[0], newRow0);
	_mm_storeu_ps(result.m_elements[1], newRow1);
	_mm_storeu_ps(result.m_elements[2], newRow2);
	_mm_storeu_ps(result.m_elements[3], newRow3);

	return result;
}

inline mat4 operator*(const mat4& a, const float& f)
{
	mat4 result;

	__m128 otherRow0 = _mm_load_ps(a.m_elements[0]);
	__m128 otherRow1 = _mm_load_ps(a.m_elements[1]);
	__m128 otherRow2 = _mm_load_ps(a.m_elements[2]);
	__m128 otherRow3 = _mm_load_ps(a.m_elements[3]);

	__m128 newRow0 = _mm_mul_ps(otherRow0, _mm_set1_ps(f));
	__m128 newRow1 = _mm_mul_ps(otherRow1, _mm_set1_ps(f));
	__m128 newRow2 = _mm_mul_ps(otherRow2, _mm_set1_ps(f));
	__m128 newRow3 = _mm_mul_ps(otherRow3, _mm_set1_ps(f));

	_mm_storeu_ps(result.m_elements[0], newRow0);
	_mm_storeu_ps(result.m_elements[1], newRow1);
	_mm_storeu_ps(result.m_elements[2], newRow2);
	_mm_storeu_ps(result.m_elements[3], newRow3);

	return result;
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
