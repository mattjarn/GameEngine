#ifndef QUAT_H
#define QUAT_H

#include <math.h>
#include <xmmintrin.h>
#include <pmmintrin.h>
#include "vec4.h"
#include "mat4.h"

# define PI           3.14159265358979323846  /* pi */


struct quat
{
	float elts[4];

	quat() {
		this->elts[0] = 0;  this->elts[1] = 0; this->elts[2] = 0; this->elts[3] = 1;
	};
	quat(vec4 v, float angle) {
		angle = PI / 180 * angle;
		float s = sin(angle / 2);

		this->elts[0] = v.elts[0] * s;
		this->elts[1] = v.elts[1] * s;
		this->elts[2] = v.elts[2] * s;
		this->elts[3] = cos(angle / 2);
	};
	quat(float fx, float fy, float fz) {
		this->elts[0] = fx;
		this->elts[1] = fy;
		this->elts[2] = fz;
	};

	static void print(quat q) {
		std::cout << "the quaternion is: " << q.elts[0] << ", " << q.elts[1] << ", " << q.elts[2] << ", " << q.elts[3] << std::endl;
	};

	static vec4 cross(const quat& a, const vec4& b) {
		vec4 result;
		result.elts[0] = a.elts[1] * b.elts[2] - a.elts[2] * b.elts[1];
		result.elts[1] = a.elts[2] * b.elts[0] - a.elts[0] * b.elts[2];
		result.elts[2] = a.elts[0] * b.elts[1] - a.elts[1] * b.elts[0];
		result.elts[3] = 0;
		return result;
	};

	static mat4 getMatrix(quat a) {
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
	};

	static vec4 rotate(quat q, vec4 v) {
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
		result.elts[0] = (((1 - (num5 + num6)) * v.elts[0] + (num7 - num12) * v.elts[1] + (num8 + num11) * v.elts[2]));
		result.elts[1] = (((num7 + num12) * v.elts[0] + (1 - (num4 + num6)) * v.elts[1] + (num9 - num10) * v.elts[2]));
		result.elts[2] = (((num8 - num11) * v.elts[0] + (num9 + num10) * v.elts[1] + (1 - (num4 + num5)) * v.elts[2]));
		result.elts[3] = 0;
		return result;
	};

	static quat mulQuaternion(quat a, quat x) {
		quat result;
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
	};

	static quat conjugate(quat a) {
		quat result;
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
	};


};

extern inline quat operator+(const quat& a, const quat& b);
extern inline quat operator-(const quat& lhs, const quat& rhs);
extern inline vec4 operator*(const quat& q, const vec4& v);
extern inline quat operator*(const quat& lhs, const float& rhs);

#endif //QUAT_H