#ifndef MAT4
#define MAT4

#include <math.h>
#include "vec4.h"
#include <xmmintrin.h>
#include <iostream>

# define PI           3.14159265358979323846  /* pi */

struct mat4
{
	float m_elements[4][4];

	mat4() {
		m_elements[0][0] = 1;  m_elements[0][1] = 0; m_elements[0][2] = 0; m_elements[0][3] = 0;
		m_elements[1][0] = 0;  m_elements[1][1] = 1; m_elements[1][2] = 0; m_elements[1][3] = 0;
		m_elements[2][0] = 0;  m_elements[2][1] = 0; m_elements[2][2] = 1; m_elements[2][3] = 0;
		m_elements[3][0] = 0;  m_elements[3][1] = 0; m_elements[3][2] = 0; m_elements[3][3] = 1;
	};
	mat4(float f) {
		m_elements[0][0] = f;  m_elements[0][1] = 0; m_elements[0][2] = 0; m_elements[0][3] = 0;
		m_elements[1][0] = 0;  m_elements[1][1] = f; m_elements[1][2] = 0; m_elements[1][3] = 0;
		m_elements[2][0] = 0;  m_elements[2][1] = 0; m_elements[2][2] = f; m_elements[2][3] = 0;
		m_elements[3][0] = 0;  m_elements[3][1] = 0; m_elements[3][2] = 0; m_elements[3][3] = 1;
	};

	mat4(float fx, float fy, float fz) {
		m_elements[0][0] = fx;  m_elements[0][1] = 0; m_elements[0][2] = 0; m_elements[0][3] = 0;
		m_elements[1][0] = 0;  m_elements[1][1] = fy; m_elements[1][2] = 0; m_elements[1][3] = 0;
		m_elements[2][0] = 0;  m_elements[2][1] = 0; m_elements[2][2] = fz; m_elements[2][3] = 0;
		m_elements[3][0] = 0;  m_elements[3][1] = 0; m_elements[3][2] = 0; m_elements[3][3] = 1;
	};

	static void getFloatValues(mat4 m, float f[]) {
		f[0] = m.m_elements[0][0]; 	f[1] = m.m_elements[0][1]; 	f[2] = m.m_elements[0][2]; 	f[3] = m.m_elements[0][3];
		f[4] = m.m_elements[1][0]; 	f[5] = m.m_elements[1][1]; 	f[6] = m.m_elements[1][2]; 	f[7] = m.m_elements[1][3];
		f[8] = m.m_elements[2][0]; 	f[9] = m.m_elements[2][1]; 	f[10] = m.m_elements[2][2]; 	f[11] = m.m_elements[2][3];
		f[12] = m.m_elements[3][0];		f[13] = m.m_elements[3][1]; 	f[14] = m.m_elements[3][2]; 	f[15] = m.m_elements[3][3];
	};

	static void print(mat4 m) {
		std::cout << "the matrix is: " << std::endl;
		std::cout << m.m_elements[0][0] << " " << m.m_elements[0][1] << " " << m.m_elements[0][2] << " " << m.m_elements[0][3] << std::endl;
		std::cout << m.m_elements[1][0] << " " << m.m_elements[1][1] << " " << m.m_elements[1][2] << " " << m.m_elements[1][3] << std::endl;
		std::cout << m.m_elements[2][0] << " " << m.m_elements[2][1] << " " << m.m_elements[2][2] << " " << m.m_elements[2][3] << std::endl;
		std::cout << m.m_elements[3][0] << " " << m.m_elements[3][1] << " " << m.m_elements[3][2] << " " << m.m_elements[3][3] << std::endl;
	};

	static mat4 scale(mat4 mat, const float& f) {
		mat4 m = mat;
		m.m_elements[0][0] = m.m_elements[0][0] * f;
		m.m_elements[1][1] = m.m_elements[1][1] * f;
		m.m_elements[2][2] = m.m_elements[2][2] * f;
		return m;
	};

	static mat4 scale(mat4 mat, vec4 v) {
		mat4 m = mat;
		m.m_elements[0][0] = m.m_elements[0][0] * v.elts[0];
		m.m_elements[1][1] = m.m_elements[1][1] * v.elts[1];
		m.m_elements[2][2] = m.m_elements[2][2] * v.elts[2];
		return m;
	};

	static mat4 translate(mat4 mat, vec4 v) {
		mat4 m = mat;
		m.m_elements[3][0] = v.elts[0];  m.m_elements[3][1] = v.elts[1]; m.m_elements[3][2] = v.elts[2];
		return m;
	};

	static mat4 createTranslationMat(const float& Tx, const float& Ty, const float& Tz);
	static mat4 createTranslationMat(const vec4& v);


	static mat4 createRotateX(const float& degrees);
	static mat4 createRotateY(const float& degrees);
	static mat4 createRotateZ(const float& degrees);

	static mat4 createRotationMat(const float& degreesX, const float& degreesY, const float& degreesZ);

	static mat4 lookAt(vec4 eye, vec4 target, vec4 y) {
		mat4 look;

		vec4 Fwd = vec4::normalize((target - eye));
		vec4 Y = y;
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
	};

	static mat4 perspective(float fovy, float aspect, float n, float f) {
		float q = 1.0f / ((float)tan(0.5f * fovy));
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
	};

	static mat4 ortho(float left, float right, float top, float bottom, float n, float f) {
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
		m.m_elements[2][2] = -2.0f / (f - n);
		m.m_elements[2][3] = 0.0f;

		m.m_elements[3][0] = -(right + left) / (right - left);
		m.m_elements[3][1] = -(top + bottom) / (top - bottom);
		m.m_elements[3][2] = -(f + n) / (f - n);
		m.m_elements[3][3] = 1.0f;

		return m;
	};

	static mat4 transpose(const mat4& a) {
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
	};

	static mat4 getCofactor(mat4 A, int p, int q, int n);

	static float determinant(mat4 A, int n);

	static mat4 adjoint(mat4 A);

	static mat4 inverse(mat4 A);

	static vec4 mulVectorMatrix(const vec4& v, const mat4& a);


};

extern inline mat4 operator+(const mat4& a, const mat4& b) {
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
};

extern inline mat4 operator-(const mat4& a, const mat4& b) {
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
};
extern inline mat4 operator*(const mat4& a, const mat4& b) {
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
};
extern inline mat4 operator*(const mat4& a, const float& f) {
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
};

#endif