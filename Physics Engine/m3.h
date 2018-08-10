#pragma once
#include "v3.h"
#include "v4.h"

namespace pys
{
	class m3
	{
	public:
		m3();
		m3(double a, double b, double c, double d, double e, double f, double g, double h, double i);
		~m3();

		void setInverse(const m3 &mat);
		m3 inverse() const;
		void invert();
		void setTranspose(const m3 &mat);
		m3 transpose() const;
		void setOrientation(const v4 &vec);

		m3 operator* (const m3 &mat) const;

		double data[9];
	};
}
