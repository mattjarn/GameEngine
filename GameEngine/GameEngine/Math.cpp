#include <xmmintrin.h>
#include <pmmintrin.h>
#include <cmath>
#include <iostream>


namespace Math
{
	void mulVectorMatrix(float result[4], float v[4], float a[4][4])
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
		__m128 aRow0 = _mm_loadu_ps(a[0]);
		__m128 aRow1 = _mm_loadu_ps(a[1]);
		__m128 aRow2 = _mm_loadu_ps(a[2]);
		__m128 aRow3 = _mm_loadu_ps(a[3]);
		__m128 vec = _mm_loadu_ps(v);
		temp = _mm_mul_ps(_mm_replicate_x_ps(vec), aRow0);
		temp = _mm_madd_ps(_mm_replicate_y_ps(vec), aRow1, temp);
		temp = _mm_madd_ps(_mm_replicate_z_ps(vec), aRow2, temp);
		temp = _mm_madd_ps(_mm_replicate_w_ps(vec), aRow3, temp);

		_mm_storeu_ps(result, temp);
	}
	void mulVectorMatrix(float result[3], float v[3], float a[3][3])
	{
#define SHUFFLE_PARAM(x,y,z,w)\
	((x) | ((y) << 2 | ((z) << 4) | ((w) << 6)))
#define _mm_replicate_x_ps(v)\
	_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(0, 0, 0, 0))
#define _mm_replicate_y_ps(v)\
	_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(1, 1, 1, 1))
#define _mm_replicate_z_ps(v)\
	_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(2, 2, 2, 2))
#define _mm_madd_ps(a,b,c)\
	_mm_add_ps(_mm_mul_ps((a), (b)), (c))

		__m128 temp;
		__m128 aRow0 = _mm_loadu_ps(a[0]);
		__m128 aRow1 = _mm_loadu_ps(a[1]);
		__m128 aRow2 = _mm_loadu_ps(a[2]);
		__m128 vec = _mm_loadu_ps(v);
		temp = _mm_mul_ps(_mm_replicate_x_ps(vec), aRow0);
		temp = _mm_madd_ps(_mm_replicate_y_ps(vec), aRow1, temp);
		temp = _mm_madd_ps(_mm_replicate_z_ps(vec), aRow2, temp);

		_mm_storeu_ps(result, temp);
	}

	namespace Matrix
	{
#define N 4
		void mulVectorMatrix(float result[3], float v[3], float a[3][3])
		{
			Math::mulVectorMatrix(result, v, a);
		}
		void mulVectorMatrix(float result[4], float v[4], float a[4][4])
		{
			return Math::mulVectorMatrix(result, v, a);
		}
		void mul(float result[4][4], float a[4][4], float b[4][4])
		{
			__m128 otherRow0 = _mm_load_ps(b[0]);
			__m128 otherRow1 = _mm_load_ps(b[1]);
			__m128 otherRow2 = _mm_load_ps(b[2]);
			__m128 otherRow3 = _mm_load_ps(b[3]);

			__m128 newRow0 = _mm_mul_ps(otherRow0, _mm_set1_ps(a[0][0]));
			newRow0 = _mm_add_ps(newRow0, _mm_mul_ps(otherRow1, _mm_set1_ps(a[0][1])));
			newRow0 = _mm_add_ps(newRow0, _mm_mul_ps(otherRow2, _mm_set1_ps(a[0][2])));
			newRow0 = _mm_add_ps(newRow0, _mm_mul_ps(otherRow3, _mm_set1_ps(a[0][3])));

			__m128 newRow1 = _mm_mul_ps(otherRow0, _mm_set1_ps(a[1][0]));
			newRow1 = _mm_add_ps(newRow1, _mm_mul_ps(otherRow1, _mm_set1_ps(a[1][1])));
			newRow1 = _mm_add_ps(newRow1, _mm_mul_ps(otherRow2, _mm_set1_ps(a[1][2])));
			newRow1 = _mm_add_ps(newRow1, _mm_mul_ps(otherRow3, _mm_set1_ps(a[1][3])));

			__m128 newRow2 = _mm_mul_ps(otherRow0, _mm_set1_ps(a[2][0]));
			newRow2 = _mm_add_ps(newRow2, _mm_mul_ps(otherRow1, _mm_set1_ps(a[2][1])));
			newRow2 = _mm_add_ps(newRow2, _mm_mul_ps(otherRow2, _mm_set1_ps(a[2][2])));
			newRow2 = _mm_add_ps(newRow2, _mm_mul_ps(otherRow3, _mm_set1_ps(a[2][3])));

			__m128 newRow3 = _mm_mul_ps(otherRow0, _mm_set1_ps(a[3][0]));
			newRow3 = _mm_add_ps(newRow3, _mm_mul_ps(otherRow1, _mm_set1_ps(a[3][1])));
			newRow3 = _mm_add_ps(newRow3, _mm_mul_ps(otherRow2, _mm_set1_ps(a[3][2])));
			newRow3 = _mm_add_ps(newRow3, _mm_mul_ps(otherRow3, _mm_set1_ps(a[3][3])));

			_mm_storeu_ps(result[0], newRow0);
			_mm_storeu_ps(result[1], newRow1);
			_mm_storeu_ps(result[2], newRow2);
			_mm_storeu_ps(result[3], newRow3);
		}
		void mul(float result[3][3], float a[3][3], float b[3][3])
		{
			__m128 otherRow0 = _mm_load_ps(b[0]);
			__m128 otherRow1 = _mm_load_ps(b[1]);
			__m128 otherRow2 = _mm_load_ps(b[2]);

			__m128 newRow0 = _mm_mul_ps(otherRow0, _mm_set1_ps(a[0][0]));
			newRow0 = _mm_add_ps(newRow0, _mm_mul_ps(otherRow1, _mm_set1_ps(a[0][1])));
			newRow0 = _mm_add_ps(newRow0, _mm_mul_ps(otherRow2, _mm_set1_ps(a[0][2])));

			__m128 newRow1 = _mm_mul_ps(otherRow0, _mm_set1_ps(a[1][0]));
			newRow1 = _mm_add_ps(newRow1, _mm_mul_ps(otherRow1, _mm_set1_ps(a[1][1])));
			newRow1 = _mm_add_ps(newRow1, _mm_mul_ps(otherRow2, _mm_set1_ps(a[1][2])));

			__m128 newRow2 = _mm_mul_ps(otherRow0, _mm_set1_ps(a[2][0]));
			newRow2 = _mm_add_ps(newRow2, _mm_mul_ps(otherRow1, _mm_set1_ps(a[2][1])));
			newRow2 = _mm_add_ps(newRow2, _mm_mul_ps(otherRow2, _mm_set1_ps(a[2][2])));

			_mm_storeu_ps(result[0], newRow0);
			_mm_storeu_ps(result[1], newRow1);
			_mm_storeu_ps(result[2], newRow2);
		}
		void add(float result[4][4], float a[4][4], float b[4][4])
		{
			__m128 otherRow0 = _mm_load_ps(b[0]);
			__m128 otherRow1 = _mm_load_ps(b[1]);
			__m128 otherRow2 = _mm_load_ps(b[2]);
			__m128 otherRow3 = _mm_load_ps(b[3]);
			__m128 Row0 = _mm_load_ps(a[0]);
			__m128 Row1 = _mm_load_ps(a[1]);
			__m128 Row2 = _mm_load_ps(a[2]);
			__m128 Row3 = _mm_load_ps(a[3]);

			__m128 newRow0 = _mm_add_ps(otherRow0, Row0);
			__m128 newRow1 = _mm_add_ps(otherRow1, Row1);
			__m128 newRow2 = _mm_add_ps(otherRow2, Row2);
			__m128 newRow3 = _mm_add_ps(otherRow3, Row3);

			_mm_store_ps(result[0], newRow0);
			_mm_store_ps(result[1], newRow1);
			_mm_store_ps(result[2], newRow2);
			_mm_store_ps(result[3], newRow3);
		}
		void add(float result[3][3], float a[3][3], float b[3][3])
		{
			__m128 otherRow0 = _mm_load_ps(b[0]);
			__m128 otherRow1 = _mm_load_ps(b[1]);
			__m128 otherRow2 = _mm_load_ps(b[2]);
			__m128 Row0 = _mm_load_ps(a[0]);
			__m128 Row1 = _mm_load_ps(a[1]);
			__m128 Row2 = _mm_load_ps(a[2]);

			__m128 newRow0 = _mm_add_ps(otherRow0, Row0);
			__m128 newRow1 = _mm_add_ps(otherRow1, Row1);
			__m128 newRow2 = _mm_add_ps(otherRow2, Row2);

			_mm_store_ps(result[0], newRow0);
			_mm_store_ps(result[1], newRow1);
			_mm_store_ps(result[2], newRow2);
		}
		void sub(float result[4][4], float a[4][4], float b[4][4])
		{
			__m128 otherRow0 = _mm_load_ps(b[0]);
			__m128 otherRow1 = _mm_load_ps(b[1]);
			__m128 otherRow2 = _mm_load_ps(b[2]);
			__m128 otherRow3 = _mm_load_ps(b[3]);
			__m128 Row0 = _mm_load_ps(a[0]);
			__m128 Row1 = _mm_load_ps(a[1]);
			__m128 Row2 = _mm_load_ps(a[2]);
			__m128 Row3 = _mm_load_ps(a[3]);

			__m128 newRow0 = _mm_sub_ps(otherRow0, Row0);
			__m128 newRow1 = _mm_sub_ps(otherRow1, Row1);
			__m128 newRow2 = _mm_sub_ps(otherRow2, Row2);
			__m128 newRow3 = _mm_sub_ps(otherRow3, Row3);

			_mm_store_ps(result[0], newRow0);
			_mm_store_ps(result[1], newRow1);
			_mm_store_ps(result[2], newRow2);
			_mm_store_ps(result[3], newRow3);
		}
		void sub(float result[3][3], float a[3][3], float b[3][3])
		{
			__m128 otherRow0 = _mm_load_ps(b[0]);
			__m128 otherRow1 = _mm_load_ps(b[1]);
			__m128 otherRow2 = _mm_load_ps(b[2]);
			__m128 Row0 = _mm_load_ps(a[0]);
			__m128 Row1 = _mm_load_ps(a[1]);
			__m128 Row2 = _mm_load_ps(a[2]);

			__m128 newRow0 = _mm_sub_ps(otherRow0, Row0);
			__m128 newRow1 = _mm_sub_ps(otherRow1, Row1);
			__m128 newRow2 = _mm_sub_ps(otherRow2, Row2);

			_mm_store_ps(result[0], newRow0);
			_mm_store_ps(result[1], newRow1);
			_mm_store_ps(result[2], newRow2);
		}
		void transpose(float result[4][4], float a[4][4])
		{
			float transMat[4][4];
			for (int row = 0; row < 4; row++)
			{
				for (int col = 0; col < 4; col++)
				{
					transMat[row][col] = a[col][row];
				}
			}
			__m128 transRow0 = _mm_loadu_ps(transMat[0]);
			__m128 transRow1 = _mm_loadu_ps(transMat[1]);
			__m128 transRow2 = _mm_loadu_ps(transMat[2]);
			__m128 transRow3 = _mm_loadu_ps(transMat[3]);

			_mm_storeu_ps(result[0], transRow0);
			_mm_storeu_ps(result[1], transRow1);
			_mm_storeu_ps(result[2], transRow2);
			_mm_storeu_ps(result[3], transRow3);
		}
		void transpose(float result[3][3], float a[3][3])
		{
			float transMat[3][3];
			for (int row = 0; row < 3; row++)
			{
				for (int col = 0; col < 3; col++)
				{
					transMat[row][col] = a[col][row];
				}
			}
			__m128 transRow0 = _mm_loadu_ps(transMat[0]);
			__m128 transRow1 = _mm_loadu_ps(transMat[1]);
			__m128 transRow2 = _mm_loadu_ps(transMat[2]);

			_mm_storeu_ps(result[0], transRow0);
			_mm_storeu_ps(result[1], transRow1);
			_mm_storeu_ps(result[2], transRow2);
		}

		//This section is for the inverse of a matrix (4v4).  This was taken from https://www.geeksforgeeks.org/adjoint-inverse-matrix/.
		void getCofactor(float A[N][N], float temp[N][N], int p, int q, int n)
		{
			int i = 0, j = 0;

			// Looping for each element of the matrix
			for (int row = 0; row < n; row++)
			{
				for (int col = 0; col < n; col++)
				{
					//  Copying into temporary matrix only those element
					//  which are not in given row and column
					if (row != p && col != q)
					{
						temp[i][j++] = A[row][col];

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
		}

		float determinant(float A[N][N], int n)
		{
			float D = 0; // Initialize result

						 //  Base case : if matrix contains single element
			if (n == 1)
				return A[0][0];

			float temp[N][N]; // To store cofactors

			int sign = 1;  // To store sign multiplier

						   // Iterate for each element of first row
			for (int f = 0; f < n; f++)
			{
				// Getting Cofactor of A[0][f]
				getCofactor(A, temp, 0, f, n);
				D += sign * A[0][f] * determinant(temp, n - 1);

				// terms are to be added with alternate sign
				sign = -sign;
			}

			return D;
		}

		void adjoint(float A[N][N], float adj[N][N])
		{
			if (N == 1)
			{
				adj[0][0] = 1;
				return;
			}

			// temp is used to store cofactors of A[][]
			int sign = 1;
			float temp[N][N];

			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					// Get cofactor of A[i][j]
					getCofactor(A, temp, i, j, N);

					// sign of adj[j][i] positive if sum of row
					// and column indexes is even.
					sign = ((i + j) % 2 == 0) ? 1 : -1;

					// Interchanging rows and columns to get the
					// transpose of the cofactor matrix
					adj[j][i] = (sign)*(determinant(temp, N - 1));
				}
			}
		}

		bool inverse(float A[N][N], float inverse[N][N])
		{
			// Find determinant of A[][]
			float det = determinant(A, N);
			if (det == 0)
			{
				return false;
			}

			// Find adjoint
			float adj[N][N];
			adjoint(A, adj);

			// Find Inverse using formula "inverse(A) = adj(A)/det(A)"
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					inverse[i][j] = adj[i][j] / float(det);

			return true;
		}
	}

	namespace Vector
	{
		void mulVectorMatrix(float result[3], float v[3], float a[3][3])
		{
			Math::mulVectorMatrix(result, v, a);
		}
		void mulVectorMatrix(float result[4], float v[4], float a[4][4])
		{
			return Math::mulVectorMatrix(result, v, a);
		}
		void addVector3(float result[3], float a[3], float b[3])
		{
			__m128 vector1 = _mm_loadu_ps(b);
			__m128 vector2 = _mm_loadu_ps(a);
			_mm_storeu_ps(result, _mm_add_ps(vector1, vector2));
		}
		void addVector4(float result[4], float a[4], float b[4])
		{
			__m128 vector1 = _mm_loadu_ps(b);
			__m128 vector2 = _mm_loadu_ps(a);
			_mm_storeu_ps(result, _mm_add_ps(vector1, vector2));
		}
		void dotVector3(float& result, float a[3], float b[3])
		{
			result = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
		}
		void dotVector4(float& result, float a[4], float b[4])
		{
			result = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
		}
		void crossVector3(float result[3], float a[3], float b[3])
		{
			result[0] = a[1] * b[2] - a[2] * b[1];
			result[1] = a[2] * b[0] - a[0] * b[2];
			result[2] = a[0] * b[1] - a[1] * b[0];
		}
		void magSqdVector3(float& result, float a[3])
		{
			result = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
		}
		void magSqdVector4(float& result, float a[4])
		{
			result = a[0] * a[0] + a[1] * a[1] + a[2] * a[2] + a[3] * a[3];
		}
		void magVector3(float& result, float a[3])
		{
			Math::Vector::magSqdVector3(result, a);
			result = sqrt(result);
		}
		void magVector4(float& result, float a[4])
		{
			Math::Vector::magSqdVector4(result, a);
			result = sqrt(result);
		}
		void scaleVector4(float result[4], float a[4], float scale)
		{
			__m128 vector = _mm_loadu_ps(a);
			__m128 temp = _mm_mul_ps(vector, _mm_set1_ps(scale));
			_mm_storeu_ps(result, temp);
		}
		void scaleVector3(float result[3], float a[3], float scale)
		{
			float temp1[4];
			__m128 vector = _mm_loadu_ps(a);
			__m128 temp = _mm_mul_ps(vector, _mm_set1_ps(scale));
			_mm_storeu_ps(temp1, temp);
			result[0] = temp1[0];
			result[1] = temp1[1];
			result[2] = temp1[2];
		}
	}

	namespace Quaternion
	{
		//Got this from the web, requires SSE3 intrinsics, which is why I have included <pmmintrin.h> 
		//https://stackoverflow.com/questions/18542894/how-to-multiply-two-quaternions-with-minimal-instructions, 
		//This was necessary to implement the horizontal add and sub methods, without which writing this
		//function is a giant pain in the asshole, in my opinion. I tried it for like an hour...then
		//promptly ran back to the SSE3 implementation.
		void mulQuaternion(float result[4], float a[4], float x[4])
		{
			__m128 xyzw = _mm_loadu_ps(x);
			__m128 abcd = _mm_loadu_ps(a);

			__m128 wzyx = _mm_shuffle_ps(xyzw, xyzw, _MM_SHUFFLE(0, 1, 2, 3));
			__m128 baba = _mm_shuffle_ps(abcd, abcd, _MM_SHUFFLE(0, 1, 0, 1));
			__m128 dcdc = _mm_shuffle_ps(abcd, abcd, _MM_SHUFFLE(2, 3, 2, 3));
			__m128 ZnXWY = _mm_hsub_ps(_mm_mul_ps(xyzw, baba), _mm_mul_ps(wzyx, dcdc));
			__m128 XZYnW = _mm_hadd_ps(_mm_mul_ps(xyzw, dcdc), _mm_mul_ps(wzyx, baba));
			__m128 XZWY = _mm_addsub_ps(_mm_shuffle_ps(XZYnW, ZnXWY, _MM_SHUFFLE(3, 2, 1, 0)), _mm_shuffle_ps(ZnXWY, XZYnW, _MM_SHUFFLE(2, 3, 0, 1)));
			__m128 resultSIMD = _mm_shuffle_ps(XZWY, XZWY, _MM_SHUFFLE(2, 1, 3, 0));
			_mm_storeu_ps(result, resultSIMD);
		}
		void conjugateQuaternion(float result[4], float a[4])
		{
			result[0] = -a[0];
			result[1] = -a[1];
			result[2] = -a[2];
		}
		void rotateQuaternion(float result[4], float a[4], float q[4])
		{
			float qautMatrix[3][3] = { 1 - 2 * q[1] * q[1] - 2 * q[2] * q[2]	, 2 * (q[0] * q[1] + q[2] * q[3])		, 2 * (q[0] * q[2] - q[1] * q[3]),
				2 * (q[0] * q[1] - q[2] * q[3])			, 1 - 2 * q[0] * q[0] - 2 * q[2] * q[2]	, 2 * (q[1] * q[2] + q[0] * q[3]),
				2 * (q[0] * q[2] + q[1] * q[3])			, 2 * (q[1] * q[2] - q[0] * q[3])		, 1 - 2 * q[0] * q[0] - 2 * q[1] * q[1] };


		}
	}
}

int doSomething()
{
	float test[4] = { 0, 1, 2, 3 };
	float a[4] = { 0, 1, 2, 3 };
	float b[4] = { 0, 1, 2, 3 };
	float result[4];
	Math::Vector::dotVector4(*result, a, b);

	std::cout << "the resulting vector is: " << result[0] << ", " << result[1] << ", " << result[2] << ", " << result[3] << std::endl;


	//Allocator * poolAllocator = new PoolAllocator(5000 * sizeof(test), sizeof(test));
	//poolAllocator->Init();
	//poolAllocator->Allocate(sizeof(test), sizeof(test));
	return 0;
}






