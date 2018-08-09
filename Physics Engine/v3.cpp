#include "v3.h"

namespace pys {
	v3::v3() {
		x = 0; y = 0; z = 0;
	}

	v3::v3(double x, double y, double z) {
		this->x = x; this->y = y; this->z = z;
	}

	void v3::clr() {
		x = 0;
		y = 0;
		z = 0;
	}

	void v3::inv() { x *= -1; y *= -1; z *= -1; }

	double v3::len() const {
		return sqrt(x*x + y*y + z*z);
	}

	double v3::lenSqr() const {
		return x*x + y*y + z*z;
	}

	void v3::normalise() {
		double l = this->len();

		if (l == 0) return;

		x /= l;
		y /= l;
		z /= l;
	}

	double v3::sclrprd(const v3 & rhs) const {
		return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z;
	}

	v3 v3::dot(const v3 & rhs) const {
		return v3(this->y * rhs.z - this->z * rhs.y,
			this->z * rhs.x - this->x * rhs.z,
			this->x * rhs.y - this->y * rhs.x);
	}

	const v3 & v3::operator *= (const v3 & rhs) {
		this->x *= rhs.x;
		this->y *= rhs.y;
		this->z *= rhs.z;

		return *this;
	}

	const v3 & v3::operator /= (const v3 & rhs) {
		this->x /= rhs.x;
		this->y /= rhs.y;
		this->z /= rhs.z;

		return *this;
	}

	const v3 & v3::operator += (const v3 & rhs) {
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;

		return *this;
	}

	const v3 & v3::operator -= (const v3 & rhs) {
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;

		return *this;
	}

	v3 v3::operator * (const v3 & rhs) const {
		return v3(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z);
	}

	v3 v3::operator / (const v3 & rhs) const {
		return v3(this->x / rhs.x, this->y / rhs.y, this->z / rhs.z);
	}

	v3 v3::operator + (const v3 & rhs) const {
		return v3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
	}

	v3 v3::operator - (const v3 & rhs) const {
		return v3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
	}

	const v3 & v3::operator *= (const double rhs) {
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;

		return *this;
	}

	const v3 & v3::operator /= (const double rhs) {
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;

		return *this;
	}

	const v3 & v3::operator += (const double rhs) {
		this->x += rhs;
		this->y += rhs;
		this->z += rhs;

		return *this;
	}

	const v3 & v3::operator -= (const double rhs) {
		this->x -= rhs;
		this->y -= rhs;
		this->z -= rhs;

		return *this;
	}

	v3 v3::operator * (const double rhs) const {
		return v3(this->x * rhs, this->y * rhs, this->z * rhs);
	}

	v3 v3::operator / (const double rhs) const {
		return v3(this->x / rhs, this->y / rhs, this->z / rhs);
	}

	v3 v3::operator + (const double rhs) const {
		return v3(this->x + rhs, this->y + rhs, this->z + rhs);
	}

	v3 v3::operator - (const double rhs) const {
		return v3(this->x - rhs, this->y - rhs, this->z - rhs);
	}
}