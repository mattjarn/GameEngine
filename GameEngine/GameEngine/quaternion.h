#ifndef QUATERNION
#define QUATERNION

#include <math.h>
#include <xmmintrin.h>
#include <pmmintrin.h>
#include "vec4.h"
#include "mat4.h"

# define PI           3.14159265358979323846  /* pi */


struct quaternion
{
	float elts[4];

	quaternion();
	quaternion(vec4 v, float angle);

	static void print(quaternion q);

	static vec4 cross(const quaternion& a, const vec4& b);

	static mat4 getMatrix(quaternion a);
	
	static vec4 rotate(quaternion q, vec4 v);

	static quaternion mulQuaternion(quaternion a, quaternion x);

	static quaternion conjugate(quaternion a);


};

extern inline quaternion operator+(const quaternion& a, const quaternion& b);
extern inline quaternion operator-(const quaternion& lhs, const quaternion& rhs);
extern inline vec4 operator*(const quaternion& q, const vec4& v);
extern inline quaternion operator*(const quaternion& lhs, const float& rhs);

#endif