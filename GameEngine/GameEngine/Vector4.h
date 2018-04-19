#ifndef VECTOR4_H
#define VECTOR4_H

#include <math.h>
#include <xmmintrin.h>
#include <iostream>

class vector4
{
	float elts[4];

	vector4() {
		this->elts[0] = 0;  this->elts[1] = 0; this->elts[2] = 0; this->elts[3] = 1;
	}
	vector4(float x, float y, float z) {
		this->elts[0] = x;  this->elts[1] = y; this->elts[2] = z; this->elts[3] = 1;
	}

	static void print(vector4 v) {
		std::cout << "the vector is: " << v.elts[0] << ", " << v.elts[1] << ", " << v.elts[2] << ", " << v.elts[3] << std::endl;
	}

	static float dot(const vector4& a, const vector4& b) {
		return (a.elts[0] * b.elts[0] + a.elts[1] * b.elts[1] + a.elts[2] * b.elts[2]);
	}

	static vector4 cross(const vector4& a, const vector4& b) {
		vector4 result;
		result.elts[0] = a.elts[1] * b.elts[2] - a.elts[2] * b.elts[1];
		result.elts[1] = a.elts[2] * b.elts[0] - a.elts[0] * b.elts[2];
		result.elts[2] = a.elts[0] * b.elts[1] - a.elts[1] * b.elts[0];
		result.elts[3] = 0;
		return result;
	}

	static vector4 scale(const vector4& a, float f);

	static vector4 normalize(const vector4& v);

};

extern inline vector4 operator+(const vector4& lhs, const vector4& rhs);
extern inline vector4 operator-(const vector4& lhs, const vector4& rhs);
extern inline float operator*(const vector4* lhs, const vector4& rhs);
extern inline vector4 operator*(const vector4& lhs, const float& rhs);

#endif