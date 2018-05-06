#ifndef VEC4
#define VEC4

#include <math.h>
#include <xmmintrin.h>
#include <iostream>

struct vec4
{
	float elts[4];

	vec4() {
		this->elts[0] = 0;  this->elts[1] = 0; this->elts[2] = 0; this->elts[3] = 1;
	};
	vec4(float x, float y, float z) {
		this->elts[0] = x;  this->elts[1] = y; this->elts[2] = z; this->elts[3] = 1;
	};
	vec4(float x, float y, float z, float w) {
		this->elts[0] = x;  this->elts[1] = y; this->elts[2] = z; this->elts[3] = w;
	};

	static void print(vec4 v) {
		std::cout << "the vector is: " << v.elts[0] << ", " << v.elts[1] << ", " << v.elts[2] << ", " << v.elts[3] << std::endl;
	};

	static float dot(const vec4& a, const vec4& b);

	static vec4 cross(const vec4& a, const vec4& b);

	static vec4 scale(const vec4& a, float f);

	static vec4 normalize(const vec4& v);

};

extern inline vec4 operator+(const vec4& lhs, const vec4& rhs);
extern inline vec4 operator-(const vec4& lhs, const vec4& rhs);
extern inline float operator*(const vec4* lhs, const vec4& rhs);
extern inline vec4 operator*(const vec4& lhs, const float& rhs);

#endif