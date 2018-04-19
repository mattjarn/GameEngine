#include "quaternion.h"

quaternion::quaternion() {
	this->elts[0] = 0;  this->elts[1] = 0; this->elts[2] = 0; this->elts[3] = 1;
}

quaternion::quaternion(vec4 v, float angle) {

	angle = PI / 180 * angle;
	float s = sin(angle / 2);

	this->elts[0] = v.elts[0] * s;
	this->elts[1] = v.elts[1] * s;
	this->elts[2] = v.elts[2] * s;
	this->elts[3] = cos(angle / 2);
}

void quaternion::print(quaternion q) {
	std::cout << "the quaternion is: " << q.elts[0] << ", " << q.elts[1] << ", " << q.elts[2] << ", " << q.elts[3] << std::endl;
}

vec4 quaternion::cross(const quaternion& a, const vec4& b) {
	vec4 result;
	result.elts[0] = a.elts[1] * b.elts[2] - a.elts[2] * b.elts[1];
	result.elts[1] = a.elts[2] * b.elts[0] - a.elts[0] * b.elts[2];
	result.elts[2] = a.elts[0] * b.elts[1] - a.elts[1] * b.elts[0];
	result.elts[3] = 0;
	return result;
}

vec4 quaternion::rotate(quaternion q, vec4 v) {
	vec4 result;

	result.elts[0] = q.elts[0] * v.elts[0] * -q.elts[0];
	result.elts[1] = q.elts[1] * v.elts[1] * -q.elts[1];
	result.elts[2] = q.elts[2] * v.elts[2] * -q.elts[2];
	result.elts[3] = q.elts[3] * v.elts[3] * -q.elts[3];

	return result;

}

mat4 quaternion::getMatrix(quaternion a) {
	mat4 m;

	m.m_elements[0][0] = roundf(1 - (2 * pow(a.elts[1], 2)) - (2 * pow(a.elts[2], 2)));
	m.m_elements[0][1] = roundf(2 * a.elts[0] * a.elts[1] - 2 * a.elts[2] * a.elts[3]);
	m.m_elements[0][2] = roundf(2 * a.elts[0] * a.elts[2] - 2 * a.elts[1] * a.elts[3]);
	m.m_elements[1][0] = roundf(2 * a.elts[0] * a.elts[1] - 2 * a.elts[2] * a.elts[3]);
	m.m_elements[1][1] = roundf(1 - (2 * pow(a.elts[0], 2)) - (2 * pow(a.elts[2], 2)));
	m.m_elements[1][2] = roundf(2 * a.elts[1] * a.elts[2] - 2 * a.elts[0] * a.elts[3]);
	m.m_elements[2][0] = roundf(2 * a.elts[0] * a.elts[2] - 2 * a.elts[1] * a.elts[3]);
	m.m_elements[2][1] = roundf(2 * a.elts[1] * a.elts[2] - 2 * a.elts[0] * a.elts[3]);
	m.m_elements[2][2] = roundf(1 - (2 * pow(a.elts[0], 2)) - (2 * pow(a.elts[1], 2)));

	return m;
}





//Got this from the web, requires SSE3 intrinsics, which is why I have included <pmmintrin.h> 
//https://stackoverflow.com/questions/18542894/how-to-multiply-two-quaternions-with-minimal-instructions, 
//This was necessary to implement the horizontal add and sub methods, without which writing this
//function is a giant pain in the asshole, in my opinion. I tried it for like an hour...then
//promptly ran back to the SSE3 implementation.
quaternion quaternion::mulQuaternion(quaternion a, quaternion x)
{
	quaternion result;
	__m128 xyzw = _mm_loadu_ps(x.elts);
	__m128 abcd = _mm_loadu_ps(a.elts);

	__m128 wzyx = _mm_shuffle_ps(xyzw, xyzw, _MM_SHUFFLE(0, 1, 2, 3));
	__m128 baba = _mm_shuffle_ps(abcd, abcd, _MM_SHUFFLE(0, 1, 0, 1));
	__m128 dcdc = _mm_shuffle_ps(abcd, abcd, _MM_SHUFFLE(2, 3, 2, 3));
	__m128 ZnXWY = _mm_hsub_ps(_mm_mul_ps(xyzw, baba), _mm_mul_ps(wzyx, dcdc));
	__m128 XZYnW = _mm_hadd_ps(_mm_mul_ps(xyzw, dcdc), _mm_mul_ps(wzyx, baba));
	__m128 XZWY = _mm_addsub_ps(_mm_shuffle_ps(XZYnW, ZnXWY, _MM_SHUFFLE(3, 2, 1, 0)), _mm_shuffle_ps(ZnXWY, XZYnW, _MM_SHUFFLE(2, 3, 0, 1)));
	__m128 resultSIMD = _mm_shuffle_ps(XZWY, XZWY, _MM_SHUFFLE(2, 1, 3, 0));
	_mm_storeu_ps(result.elts, resultSIMD);

	return result;
}
quaternion quaternion::conjugate(quaternion a)
{
	quaternion result;
	if (a.elts[0] != 0) {
		result.elts[0] = -a.elts[0];
	}
	else {
		result.elts[0] = 0;
	}
	if (a.elts[1] != 0) {
		result.elts[1] = -a.elts[1];
	}
	else {
		result.elts[1] = 0;
	}
	if (a.elts[2] != 0) {
		result.elts[2] = -a.elts[2];
	}
	else {
		result.elts[2] = 0;
	}
	result.elts[3] = a.elts[3];
	return result;
}

inline vec4 operator*(const quaternion& q, const vec4& v)
{
	float num = q.elts[0] * 2;
	float num2 = q.elts[1] * 2;
	float num3 = q.elts[2] * 2;
	float num4 = q.elts[0] * num;
	float num5 = q.elts[1] * num2;
	float num6 = q.elts[2] * num3;
	float num7 = q.elts[0] * num2;
	float num8 = q.elts[0] * num3;
	float num9 = q.elts[1] * num3;
	float num10 = q.elts[3] * num;
	float num11 = (q.elts[3]) * (num2);
	float num12 = q.elts[3] * num3;
	vec4 result;
	result.elts[0] = ( ( (1 - (num5 + num6) ) * v.elts[0] + (num7 - num12) * v.elts[1] + (num8 + num11) * v.elts[2]) );
	result.elts[1] = (((num7 + num12) * v.elts[0] + (1 - (num4 + num6)) * v.elts[1] + (num9 - num10) * v.elts[2]));
	result.elts[2] = (((num8 - num11) * v.elts[0] + (num9 + num10) * v.elts[1] + (1 - (num4 + num5)) * v.elts[2]));
	result.elts[3] = 0;
	return result;
}
