#include "Compare.h"
#include "vectors.h"
#include <cmath>
#include <cfloat>

float CorrectDegrees(float degrees) {
	while (degrees > 360.0f) {
		degrees -= 360.0f;
	}
	while (degrees < -360.0f) {
		degrees += 360.0f;
	}
	return degrees;
}

#ifndef RAD2DEG
float RAD2DEG(float radians) {
	float degrees = radians * 57.295754f;
	degrees = CorrectDegrees(degrees);
	return degrees;
}
#endif
#ifndef DEG2RAD
float DEG2RAD(float degrees) {
	degrees = CorrectDegrees(degrees);
	float radians = degrees * 0.0174533f;
	return radians;
}
#endif

bool operator==(const vec2& l, const vec2& r) {
	return CMP(l.x, r.x) && CMP(l.y, r.y);
}

bool operator==(const physvec3& l, const physvec3& r) {
	return CMP(l.x, r.x) && CMP(l.y, r.y) && CMP(l.z, r.z);
}

bool operator!=(const vec2& l, const vec2& r) {
	return !(l == r);
}

bool operator!=(const physvec3& l, const physvec3& r) {
	return !(l == r);
}

vec2 operator+(const vec2& l, const vec2& r) {
	return{ l.x + r.x, l.y + r.y };
}

physvec3 operator+(const physvec3& l, const physvec3& r) {
	return{ l.x + r.x, l.y + r.y, l.z + r.z };
}

vec2 operator-(const vec2& l, const vec2& r) {
	return{ l.x - r.x, l.y - r.y };
}

physvec3 operator-(const physvec3& l, const physvec3& r) {
	return{ l.x - r.x, l.y - r.y, l.z - r.z };
}

vec2 operator*(const vec2& l, const vec2& r) {
	return{ l.x * r.x, l.y * r.y };
}

physvec3 operator*(const physvec3& l, const physvec3& r) {
	return{ l.x * r.x, l.y * r.y, l.z * r.z };
}

vec2 operator*(const vec2& l, float r) {
	return{ l.x * r, l.y * r };
}

physvec3 operator*(const physvec3& l, float r) {
	return{ l.x * r, l.y * r, l.z * r };
}

vec2 operator/(const vec2& l, const vec2& r) {
	return{ l.x / r.x, l.y / r.y };
}

physvec3 operator/(const physvec3& l, const physvec3& r) {
	return{ l.x / r.x, l.y / r.y, l.z / r.z };
}

vec2 operator/(const vec2& l, float r) {
	return{ l.x / r, l.y / r };
}

physvec3 operator/(const physvec3& l, float r) {
	return{ l.x / r, l.y / r, l.z / r };
}

std::ostream& operator<<(std::ostream& os, const vec2& m) {
	os << "(" << m.x << ", " << m.y << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const physvec3& m) {
	os << "(" << m.x << ", " << m.y << ", " << m.z << ")";
	return os;
}

float Dot(const vec2& l, const vec2& r) {
	return l.x * r.x + l.y * r.y;
}

float Dot(const physvec3& l, const physvec3& r) {
	return l.x * r.x + l.y * r.y + l.z * r.z;
}

vec2& operator+=(vec2& l, const vec2& r) {
	l.x += r.x;
	l.y += r.y;
	return l;
}

vec2& operator-=(vec2& l, const vec2& r) {
	l.x -= r.y;
	l.y -= r.y;
	return l;
}

vec2& operator*=(vec2& l, const vec2& r) {
	l.x *= r.x;
	l.y *= r.y;
	return l;
}

vec2& operator*=(vec2& l, const float r) {
	l.x *= r;
	l.y *= r;
	return l;
}

vec2& operator/=(vec2& l, const vec2& r) {
	l.x /= r.x;
	l.y /= r.y;
	return l;
}

vec2& operator/=(vec2& l, const float r) {
	l.x /= r;
	l.y /= r;
	return l;
}

physvec3& operator+=(physvec3& l, const physvec3& r) {
	l.x += r.x;
	l.y += r.y;
	l.z += r.z;
	return l;
}

physvec3& operator-=(physvec3& l, const physvec3& r) {
	l.x -= r.x;
	l.y -= r.y;
	l.z -= r.z;
	return l;
}

physvec3& operator*=(physvec3& l, const physvec3& r) {
	l.x *= r.x;
	l.y *= r.y;
	l.z *= r.z;
	return l;
}

physvec3& operator*=(physvec3& l, const float r) {
	l.x *= r;
	l.y *= r;
	l.z *= r;
	return l;
}

physvec3& operator/=(physvec3& l, const physvec3& r) {
	l.x /= r.x;
	l.y /= r.y;
	l.z /= r.z;
	return l;
}

physvec3& operator/=(physvec3& l, const float r) {
	l.x /= r;
	l.y /= r;
	l.z /= r;
	return l;
}

float Magnitude(const vec2& v) {
	return sqrtf(Dot(v, v));
}

float Magnitude(const physvec3& v) {
	return sqrtf(Dot(v, v));
}

float MagnitudeSq(const vec2& v) {
	return Dot(v, v);
}

float MagnitudeSq(const physvec3& v) {
	return Dot(v, v);
}

float Distance(const vec2& p1, const vec2& p2) {
	return Magnitude(p1 - p2);
}

float Distance(const physvec3& p1, const physvec3& p2) {
	return Magnitude(p1 - p2);
}

float DistanceSq(const vec2& p1, const vec2& p2) {
	return MagnitudeSq(p1 - p2);
}

float DistanceSq(const physvec3& p1, const physvec3& p2) {
	return MagnitudeSq(p1 - p2);
}

vec2 RotateVector(const vec2& vector, float degrees) {
	degrees = DEG2RAD(degrees);
	float s = sinf(degrees);
	float c = cosf(degrees);

	return vec2(
		vector.x * c - vector.y * s,
		vector.x * s + vector.y * c
	);
}

void Normalize(vec2& v) {
	v = v * (1.0f / Magnitude(v));
}

void Normalize(physvec3& v) {
	v = v * (1.0f / Magnitude(v));
}

vec2 Normalized(const vec2& v) {
	return v * (1.0f / Magnitude(v));
}
physvec3 Normalized(const physvec3& v) {
	return v * (1.0f / Magnitude(v));
}

physvec3 Cross(const physvec3& l, const physvec3& r) {
	physvec3 result;
	result.x = l.y * r.z - l.z * r.y;
	result.y = l.z * r.x - l.x * r.z;
	result.z = l.x * r.y - l.y * r.x;
	return result;
}

float Angle(const vec2& l, const vec2& r) {
	return acosf(Dot(l, r) / sqrtf(MagnitudeSq(l) * MagnitudeSq(r)));
}

float Angle(const physvec3& l, const physvec3& r) {
	return acosf(Dot(l, r) / sqrtf(MagnitudeSq(l) * MagnitudeSq(r)));
}

vec2 Project(const vec2& length, const vec2& direction) {
	float dot = Dot(length, direction);
	float magSq = MagnitudeSq(direction);
	return direction * (dot / magSq);
}

physvec3 Project(const physvec3& length, const physvec3& direction) {
	float dot = Dot(length, direction);
	float magSq = MagnitudeSq(direction);
	return direction * (dot / magSq);
}

vec2 Perpendicular(const vec2& length, const vec2& direction) {
	return length - Project(length, direction);
}

physvec3 Perpendicular(const physvec3& length, const physvec3& direction) {
	return length - Project(length, direction);
}

vec2 Reflection(const vec2& sourceVector, const vec2& normal) {
	return sourceVector - normal * (Dot(sourceVector, normal) *  2.0f);
}

physvec3 Reflection(const physvec3& sourceVector, const physvec3& normal) {
	return sourceVector - normal * (Dot(sourceVector, normal) *  2.0f);
}
