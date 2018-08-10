#include "v4.h"

namespace pys {
	v4::v4() {
		x = 0; y = 0; z = 0, a = 0;
	}

	v4::v4(double x, double y, double z, double a) {
		this->x = x; this->y = y; this->z = z; this->a = a;
	}

	void v4::clr() {
		x = 0;
		y = 0;
		z = 0;
		a = 0;
	}

	void v4::inv() { x *= -1; y *= -1; z *= -1; a *= -1;}

	double v4::len() const {
		return sqrt(x*x + y*y + z*z + a*a);
	}

	double v4::lenSqr() const {
		return x*x + y*y + z*z + a*a;
	}

	void v4::normalise() {
		double d = x * x + y * y + z * z + a * a;

		if (d == 0)
		{
			x = 1;
			return;
		}

		d = 1 / sqrt(d);
		x *= d;
		y *= d;
		z *= d;
		a *= d;
	}

	double v4::sclrprd(const v4 & rhs) const {
		return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z + this->a * rhs.a;
	}

	const v4 & v4::operator *= (const v4 & rhs) {
		this->x *= rhs.x;
		this->y *= rhs.y;
		this->z *= rhs.z;
		this->a *= rhs.a;

		return *this;
	}

	const v4 & v4::operator /= (const v4 & rhs) {
		this->x /= rhs.x;
		this->y /= rhs.y;
		this->z /= rhs.z;
		this->a /= rhs.a;

		return *this;
	}

	const v4 & v4::operator += (const v4 & rhs) {
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		this->a += rhs.a;

		return *this;
	}

	const v4 & v4::operator -= (const v4 & rhs) {
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		this->a -= rhs.a;

		return *this;
	}

	v4 v4::operator * (const v4 & rhs) const {
		return v4(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z, this->a * rhs.a);
	}

	v4 v4::operator / (const v4 & rhs) const {
		return v4(this->x / rhs.x, this->y / rhs.y, this->z / rhs.z, this->a / rhs.a);
	}

	v4 v4::operator + (const v4 & rhs) const {
		return v4(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->a + rhs.a);
	}

	v4 v4::operator - (const v4 & rhs) const {
		return v4(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->a - rhs.a);
	}

	const v4 & v4::operator *= (const double rhs) {
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;
		this->a *= rhs;

		return *this;
	}

	const v4 & v4::operator /= (const double rhs) {
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;
		this->a /= rhs;

		return *this;
	}

	const v4 & v4::operator += (const double rhs) {
		this->x += rhs;
		this->y += rhs;
		this->z += rhs;
		this->a += rhs;

		return *this;
	}

	const v4 & v4::operator -= (const double rhs) {
		this->x -= rhs;
		this->y -= rhs;
		this->z -= rhs;
		this->a -= rhs;

		return *this;
	}

	v4 v4::operator * (const double rhs) const {
		return v4(this->x * rhs, this->y * rhs, this->z * rhs, this->a * rhs);
	}

	v4 v4::operator / (const double rhs) const {
		return v4(this->x / rhs, this->y / rhs, this->z / rhs, this->a / rhs);
	}

	v4 v4::operator + (const double rhs) const {
		return v4(this->x + rhs, this->y + rhs, this->z + rhs, this->a + rhs);
	}

	v4 v4::operator - (const double rhs) const {
		return v4(this->x - rhs, this->y - rhs, this->z - rhs, this->a - rhs);
	}

	void v4::rotate(const v3 &vec3, double scale)
	{
		v4 v(0,
			vec3.x * scale,
			vec3.y * scale,
			vec3.z * scale);

		(*this) *= v;
	}

	void v4::rotate(const v3 &vec3)
	{
		v4 v(0,
			vec3.x,
			vec3.y,
			vec3.z);

		(*this) *= v;
	}

	void v4::addScaledv3(const v3 &vec3, double scale)
	{
		v4 v(0,
			vec3.x * scale,
			vec3.y * scale,
			vec3.z * scale);

		v *= *this;
		x += v.x * 0.5;
		y += v.y * 0.5;
		z += v.z * 0.5;
		a += v.a * 0.5;
	}
}