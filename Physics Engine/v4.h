#pragma once

#include <cmath>
#include "v3.h"

namespace pys {
	class v4
	{
	public:
		v4();
		v4(double x, double y, double z, double a);

		void clr();
		void inv();
		double len() const;
		double lenSqr() const;
		void normalise();
		double sclrprd(const v4 & rhs) const;
		void rotate(const v3 &vec3, double scale);
		void rotate(const v3 &vec3);
		void addScaledv3(const v3 &vec3, double scale);

		const v4 & operator *= (const v4 & rhs);
		const v4 & operator /= (const v4 & rhs);
		const v4 & operator += (const v4 & rhs);
		const v4 & operator -= (const v4 & rhs);

		v4 operator * (const v4 & rhs) const;
		v4 operator / (const v4 & rhs) const;
		v4 operator + (const v4 & rhs) const;
		v4 operator - (const v4 & rhs) const;

		const v4 & operator *= (const double rhs);
		const v4 & operator /= (const double rhs);
		const v4 & operator += (const double rhs);
		const v4 & operator -= (const double rhs);

		v4 operator * (const double rhs) const;
		v4 operator / (const double rhs) const;
		v4 operator + (const double rhs) const;
		v4 operator - (const double rhs) const;

		double x;
		double y;
		double z;
		double a;
	};
}
