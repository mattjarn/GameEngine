#ifndef VEC4
#define VEC4

#include <math.h>
#include <xmmintrin.h>


struct vec4
{
	float elts[4];

	vec4();
	vec4(float x, float y, float z);
	vec4(float x, float y, float z, float w);

	static void print(vec4 v);

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