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

	mat4();
	mat4(float f);
	mat4(float fx, float fy, float fz);

	static void getFloatValues(mat4 m, float values[]);

	static void print(mat4 m);

	static void scale(mat4 *m, const float& f);

	static mat4 createTranslationMat(const float& Tx, const float& Ty, const float& Tz);
	static mat4 createTranslationMat(const vec4& v);


	static mat4 createRotateX(const float& degrees);
	static mat4 createRotateY(const float& degrees);
	static mat4 createRotateZ(const float& degrees);

	static mat4 createRotationMat(const float& degreesX, const float& degreesY, const float& degreesZ);

	static mat4 lookAt(vec4 eye, vec4 target, vec4 y);

	static mat4 perspective(float fovy, float aspect, float n, float f);

	static mat4 ortho(float left, float right, float top, float bottom, float near, float far);

	static mat4 transpose(const mat4& a);

	static mat4 getCofactor(mat4 A, int p, int q, int n);

	static float determinant(mat4 A, int n);

	static mat4 adjoint(mat4 A);

	static mat4 inverse(mat4 A);

	static vec4 mulVectorMatrix(const vec4& v, const mat4& a);

	
};

extern inline mat4 operator+(const mat4& a, const mat4& b);
extern inline mat4 operator-(const mat4& a, const mat4& b);
extern inline mat4 operator*(const mat4& a, const mat4& b);
extern inline mat4 operator*(const mat4& a, const float& f);

#endif