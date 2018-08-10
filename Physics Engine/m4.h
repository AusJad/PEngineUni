#pragma once
#include "v3.h"
#include "v4.h"

namespace pys
{
	class m4
	{
	public:
		m4();
		m4(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l);
		~m4();

		double getDeterminant() const;
		void setInverse(const m4 & mat);
		m4 inverse() const;
		void invert();
		void setOrientationAndPos(const v4 &vec, const v3 & pos);
		v3 localToWorld(const v3 &local, const m4 &transform);
		v3 worldToLocal(const v3 &world, const m4 &transform);
		v3 transform(const v3 &vec) const;
		v3 transformInverse(const v3 &vec) const;
		v3 transformDirection(const v3  &vec) const;
		v3 transformInverseDirection(const v3 &vec) const;

		v3 operator* (const v3 & vec) const;
		m4 operator* (const m4 & mat) const;

		double data[12];
	};
}