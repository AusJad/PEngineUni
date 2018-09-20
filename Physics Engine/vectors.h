#ifndef _H_MATH_VECTORS_
#define _H_MATH_VECTORS_
#include <ostream>

//#define RAD2DEG(x) ((x) * 57.295754f)
//#define DEG2RAD(x) ((x) * 0.0174533f)

#ifndef RAD2DEG
float RAD2DEG(float radians);
#endif 
#ifndef DEG2RAD
float DEG2RAD(float degrees);
#endif
float CorrectDegrees(float degrees);

typedef struct vec2 {
	union {
		struct {
			float x;
			float y;
		};
		float asArray[2];
	};

	inline float& operator[](int i) {
		return asArray[i];
	}

	inline vec2() : x(0.0f), y(0.0f) { }
	inline vec2(float _x, float _y) : x(_x), y(_y) { }
} vec2;

typedef struct physvec3 {
	union {
		struct {
			float x;
			float y;
			float z;
		};
		float asArray[3];
	};

	inline float& operator[](int i) {
		return asArray[i];
	}

	inline physvec3() : x(0.0f), y(0.0f), z(0.0f) { }
	inline physvec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }

} physvec3;

vec2 operator+(const vec2& l, const vec2& r);
physvec3 operator+(const physvec3& l, const physvec3& r);

vec2 operator-(const vec2& l, const vec2& r);
physvec3 operator-(const physvec3& l, const physvec3& r);

vec2 operator*(const vec2& l, const vec2& r);
physvec3 operator*(const physvec3& l, const physvec3& r);

vec2 operator*(const vec2& l, float r);
physvec3 operator*(const physvec3& l, float r);

vec2 operator/(const vec2& l, const vec2& r);
physvec3 operator/(const physvec3& l, const physvec3& r);

vec2 operator/(const vec2& l, float r);
physvec3 operator/(const physvec3& l, float r);

std::ostream& operator<<(std::ostream& os, const vec2& m);
std::ostream& operator<<(std::ostream& os, const physvec3& m);

bool operator==(const vec2& l, const vec2& r);
bool operator==(const physvec3& l, const physvec3& r);

bool operator!=(const vec2& l, const vec2& r);
bool operator!=(const physvec3& l, const physvec3& r);

vec2& operator+=(vec2& l, const vec2& r);
vec2& operator-=(vec2& l, const vec2& r);
vec2& operator*=(vec2& l, const vec2& r);
vec2& operator*=(vec2& l, const float r);
vec2& operator/=(vec2& l, const vec2& r);
vec2& operator/=(vec2& l, const float r);

physvec3& operator+=(physvec3& l, const physvec3& r);
physvec3& operator-=(physvec3& l, const physvec3& r);
physvec3& operator*=(physvec3& l, const physvec3& r);
physvec3& operator*=(physvec3& l, const float r);
physvec3& operator/=(physvec3& l, const physvec3& r);
physvec3& operator/=(physvec3& l, const float r);

float Dot(const vec2& l, const vec2& r);
float Dot(const physvec3& l, const physvec3& r);

float Magnitude(const vec2& v);
float Magnitude(const physvec3& v);

float MagnitudeSq(const vec2& v);
float MagnitudeSq(const physvec3& v);

float Distance(const vec2& p1, const vec2& p2);
float Distance(const physvec3& p1, const physvec3& p2);

float DistanceSq(const vec2& p1, const vec2& p2);
float DistanceSq(const physvec3& p1, const physvec3& p2);

vec2 RotateVector(const vec2& vector, float degrees);

void Normalize(vec2& v);
void Normalize(physvec3& v);

vec2 Normalized(const vec2& v);
physvec3 Normalized(const physvec3& v);

physvec3 Cross(const physvec3& l, const physvec3& r);

float Angle(const vec2& l, const vec2& r);
float Angle(const physvec3& l, const physvec3& r);

vec2 Project(const vec2& length, const vec2& direction);
physvec3 Project(const physvec3& length, const physvec3& direction);

vec2 Perpendicular(const vec2& length, const vec2& direction);
physvec3 Perpendicular(const physvec3& length, const physvec3& direction);

vec2 Reflection(const vec2& sourceVector, const vec2& normal);
physvec3 Reflection(const physvec3& sourceVector, const physvec3& normal);

#endif