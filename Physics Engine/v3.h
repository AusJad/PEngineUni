#pragma once

#include <cmath>

namespace pys {
	class v3
	{
		public:
			v3();
			v3(double x, double y, double z);
			
			void clr();
			void inv();
			double len() const;
			double lenSqr() const;
			void normalise();
			double sclrprd(const v3 & rhs) const;
			double dot(const v3 & rhs) const;
			double squareMag() const;
			double magnitude() const;

			const v3 & operator *= (const v3 & rhs);
			const v3 & operator /= (const v3 & rhs);
			const v3 & operator += (const v3 & rhs);
			const v3 & operator -= (const v3 & rhs);

			v3 operator * (const v3 & rhs) const;
			v3 operator / (const v3 & rhs) const;
			v3 operator + (const v3 & rhs) const;
			v3 operator - (const v3 & rhs) const;

			const v3 & operator *= (const double rhs);
			const v3 & operator /= (const double rhs);
			const v3 & operator += (const double rhs);
			const v3 & operator -= (const double rhs);

			v3 operator * (const double rhs) const;
			v3 operator / (const double rhs) const;
			v3 operator + (const double rhs) const;
			v3 operator - (const double rhs) const;

			double x;
			double y;
			double z;
	};
}