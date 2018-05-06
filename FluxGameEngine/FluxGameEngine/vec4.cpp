#include "vec4.h"
#include "mat4.h"

vec4 vec4::scale(const vec4& a, float scale)
{
	vec4 result;
	__m128 vector = _mm_loadu_ps(a.elts);
	__m128 temp = _mm_mul_ps(vector, _mm_set1_ps(scale));
	_mm_storeu_ps(result.elts, temp);

	return result;
}

vec4 vec4::normalize(const vec4& v) {
	vec4 result;
	float magnitude = sqrt(v.elts[0] * v.elts[0] + v.elts[1] * v.elts[1] + v.elts[2] * v.elts[2]);
	result.elts[0] = v.elts[0] / magnitude;
	result.elts[1] = v.elts[1] / magnitude;
	result.elts[2] = v.elts[2] / magnitude;
	return result;
}

float vec4::dot(const vec4& a, const vec4& b) {
	float result;
	result = a.elts[0] * b.elts[0] + a.elts[1] * b.elts[1] + a.elts[2] * b.elts[2];
	return result;
}

vec4 vec4::cross(const vec4& a, const vec4& b) {
	vec4 result;
	result.elts[0] = a.elts[1] * b.elts[2] - a.elts[2] * b.elts[1];
	result.elts[1] = a.elts[2] * b.elts[0] - a.elts[0] * b.elts[2];
	result.elts[2] = a.elts[0] * b.elts[1] - a.elts[1] * b.elts[0];
	result.elts[3] = 0;
	return result;
}

inline vec4 operator+(const vec4& a, const vec4& b)
{
	vec4 v;
	__m128 vector1 = _mm_loadu_ps(b.elts);
	__m128 vector2 = _mm_loadu_ps(a.elts);
	_mm_storeu_ps(v.elts, _mm_add_ps(vector1, vector2));
	v.elts[3] = 1;
	return v;
}

inline vec4 operator-(const vec4& a, const vec4& b)
{
	vec4 v;
	__m128 vector1 = _mm_loadu_ps(b.elts);
	__m128 vector2 = _mm_loadu_ps(a.elts);
	_mm_storeu_ps(v.elts, _mm_sub_ps(vector1, vector2));
	v.elts[3] = 1;
	return v;
}

inline float operator*(const vec4& a, const vec4& b)
{
	float result = (a.elts[0] * b.elts[0] + a.elts[1] * b.elts[1] + a.elts[2] * b.elts[2]);
	return result;
}

inline vec4 operator*(const vec4& a, const float& scale)
{
	vec4 result;
	__m128 vector = _mm_loadu_ps(a.elts);
	__m128 temp = _mm_mul_ps(vector, _mm_set1_ps(scale));
	_mm_storeu_ps(result.elts, temp);
	result.elts[3] = 1;
	return result;
}
