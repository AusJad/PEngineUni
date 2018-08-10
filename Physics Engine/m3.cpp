#include "m3.h"

namespace pys
{
	m3::m3()
	{
		for (int i = 0; i < 9; i++)
			data[i] = 0;
	}

	m3::m3(double a, double b, double c, double d, double e, double f, double g, double h, double i)
	{
		data[0] = a;
		data[1] = b;
		data[2] = c;
		data[3] = d;
		data[4] = e;
		data[5] = f;
		data[6] = g;
		data[7] = h;
		data[8] = i;
	}

	m3::~m3()
	{

	}

	void m3::setInverse(const m3 &mat)
	{
		double t4 = mat.data[0] * mat.data[4];
		double t6 = mat.data[0] * mat.data[5];
		double t8 = mat.data[1] * mat.data[3];
		double t10 = mat.data[2] * mat.data[3];
		double t12 = mat.data[1] * mat.data[6];
		double t14 = mat.data[2] * mat.data[6];

		double t16 = (t4 * mat.data[8] - t6 * mat.data[7] - t8 * mat.data[8] + t10 * mat.data[7] + t12 * mat.data[5] - t14 * mat.data[4]);

		if (t16 == 0)
			return;

		double t17 = 1 / t16;

		data[0] = (mat.data[4] * mat.data[8] - mat.data[5] * mat.data[7]) * t17;
		data[1] = -(mat.data[1] * mat.data[8] - mat.data[2] * mat.data[7]) * t17;
		data[2] = (mat.data[1] * mat.data[5] - mat.data[2] * mat.data[4]) * t17;
		data[3] = -(mat.data[3] * mat.data[8] - mat.data[5] * mat.data[6]) * t17;
		data[4] = (mat.data[0] * mat.data[7] - t14) * t17;
		data[5] = -(t6-t10) * t17;
		data[6] = (mat.data[3] * mat.data[7] - mat.data[4] * mat.data[6]) * t17;
		data[7] = -(mat.data[0] * mat.data[7] - t12) * t17;
		data[8] = (t4 - t8) * t17;
	}

	m3 m3::inverse() const
	{
		m3 result;
		result.setInverse(*this);
		return result;
	}

	void m3::invert()
	{
		setInverse(*this);
	}

	void m3::setTranspose(const m3 &mat)
	{
		data[0] = mat.data[0];
		data[1] = mat.data[3];
		data[2] = mat.data[6];
		data[3] = mat.data[1];
		data[4] = mat.data[4];
		data[5] = mat.data[7];
		data[6] = mat.data[2];
		data[7] = mat.data[5];
		data[8] = mat.data[8];
	}

	m3 m3::transpose() const
	{
		m3 result;
		result.setTranspose(*this);
		return result;
	}

	void m3::setOrientation(const v4 & vec)
	{
		data[0] = 1 - (2 * vec.z * vec.z + 2 * vec.a * vec.a);
		data[1] = 2 * vec.y * vec.z + 2 * vec.a * vec.x;
		data[2] = 2 * vec.y * vec.a - 2 * vec.z * vec.x;
		data[3] = 2 * vec.y * vec.z - 2 * vec.a * vec.x;
		data[4] = 1 - (2 * vec.y * vec.y + 2 * vec.a * vec.a);
		data[5] = 2 * vec.y * vec.a + 2 * vec.y * vec.x;
		data[6] = 2 * vec.y * vec.a + 2 * vec.z * vec.x;
		data[7] = 2 * vec.z * vec.a + 2 * vec.y * vec.x;
		data[8] = 1 - (2 * vec.y * vec.y + 2 * vec.a * vec.a);
	}

	m3 m3::operator* (const m3 & mat) const
	{
		return m3(
			data[0] * mat.data[0] + data[1] * mat.data[3] + data[2] * mat.data[6],
			data[0] * mat.data[1] + data[1] * mat.data[4] + data[2] * mat.data[7],
			data[0] * mat.data[2] + data[1] * mat.data[5] + data[2] * mat.data[8],

			data[3] * mat.data[0] + data[4] * mat.data[3] + data[5] * mat.data[6],
			data[3] * mat.data[1] + data[4] * mat.data[4] + data[5] * mat.data[7],
			data[3] * mat.data[2] + data[4] * mat.data[5] + data[5] * mat.data[8],

			data[6] * mat.data[0] + data[7] * mat.data[3] + data[8] * mat.data[6],
			data[6] * mat.data[2] + data[7] * mat.data[4] + data[8] * mat.data[7],
			data[6] * mat.data[3] + data[7] * mat.data[5] + data[8] * mat.data[8]);
	}

}