#include "m4.h"

namespace pys
{
	m4::m4()
	{
		for (int i = 0; i < 12; i++)
			data[i] = 0;
	}

	m4::m4(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l)
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
		data[9] = j;
		data[10] = k;
		data[11] = l;
		// assuming bottom row is 0, 0, 0, 1 as per pg 175
	}

	m4::~m4()
	{

	}

	double m4::getDeterminant() const
	{
		return
			data[8] * data[5] * data[2] +
			data[4] * data[9] * data[2] +
			data[8] * data[1] * data[6] -
			data[0] * data[9] * data[6] -
			data[4] * data[1] * data[10] +
			data[0] * data[5] * data[10];
	}

	void m4::setInverse(const m4 & mat)
	{
		double det = getDeterminant();
		if (det == 0)
			return;

		det = 1.0 / det;

		data[0] = (-mat.data[9] * mat.data[6] + mat.data[5] * mat.data[10]) * det;
		data[4] = (mat.data[8] * mat.data[6] - mat.data[4] * mat.data[10]) * det;
		data[8] = (-mat.data[8] * mat.data[5] + mat.data[4] * mat.data[9]) * det; // pg 175

		data[1] = (mat.data[9] * mat.data[2] - mat.data[1] * mat.data[10]) * det;
		data[5] = (-mat.data[8] * mat.data[2] + mat.data[0] * mat.data[10]) * det;
		data[9] = (mat.data[8] * mat.data[1] - mat.data[0] * mat.data[9]) * det; // also here

		data[2] = (-mat.data[5] * mat.data[2] + mat.data[1] * mat.data[6]) * det; // also here
		data[6] = (mat.data[4] * mat.data[2] - mat.data[0] * mat.data[6]) * det; // here
		data[10] = (-mat.data[4] * mat.data[1] + mat.data[0] * mat.data[5]) * det; // here

		data[3] = (
			mat.data[9] * mat.data[6] * mat.data[3] -
			mat.data[5] * mat.data[10] * mat.data[3] -
			mat.data[9] * mat.data[2] * mat.data[7] +
			mat.data[1] * mat.data[10] * mat.data[7] +
			mat.data[5] * mat.data[2] * mat.data[11] -
			mat.data[1] * mat.data[6] * mat.data[11]) * det;

		data[7] = (
			-mat.data[8] * mat.data[6] * mat.data[3] +
			mat.data[4] * mat.data[10] * mat.data[3] +
			mat.data[8] * mat.data[2] * mat.data[7] -
			mat.data[0] * mat.data[10] * mat.data[7] -
			mat.data[4] * mat.data[2] * mat.data[11] +
			mat.data[0] * mat.data[6] * mat.data[11]) * det;

		data[11] = (
			mat.data[8] * mat.data[5] * mat.data[3] -
			mat.data[4] * mat.data[9] * mat.data[3] -
			mat.data[8] * mat.data[1] * mat.data[7] +
			mat.data[0] * mat.data[9] * mat.data[7] +
			mat.data[4] * mat.data[1] * mat.data[11] -
			mat.data[0] * mat.data[5] * mat.data[11]) * det;
	}

	m4 m4::inverse() const
	{
		m4 result;
		result.setInverse(*this);
		return result;
	}

	void m4::invert()
	{
		setInverse(*this);
	}

	void m4::setOrientationAndPos(const v4 & vec, const v3 & pos)
	{
		data[0] = 1 - (2 * vec.z * vec.z + 2 * vec.a * vec.a);
		data[1] = 2 * vec.y * vec.z + 2 * vec.a * vec.x;
		data[2] = 2 * vec.y * vec.a - 2 * vec.z * vec.x;
		data[3] = pos.x;
		data[4] = 2 * vec.y * vec.z - 2 * vec.a * vec.x;
		data[5] = 1 - (2 * vec.y * vec.y + 2 * vec.a * vec.a);
		data[6] = 2 * vec.y * vec.a + 2 * vec.y * vec.x;
		data[7] = pos.y;
		data[8] = 2 * vec.y * vec.a + 2 * vec.z * vec.x;
		data[9] = 2 * vec.z * vec.a + 2 * vec.y * vec.x;
		data[10] = 1 - (2 * vec.y * vec.y + 2 * vec.a * vec.a);
		data[11] = pos.z;
	}

	v3 m4::localToWorld(const v3 &local, const m4 &transform)
	{
		return transform.transform(local);
	}

	v3 m4::worldToLocal(const v3 &world, const m4 &transform)
	{
		return transform.transformInverse(world);
	}

	v3 m4::transform(const v3 &vec) const
	{
		return *this * vec;
	}

	v3 m4::transformInverse(const v3 & vec) const
	{
		v3 tmp = vec;
		tmp.x -= data[3];
		tmp.y -= data[7];
		tmp.z -= data[11];
		return v3(
			tmp.x * data[0] + tmp.y * data[4] + tmp.z * data[8],
			tmp.x * data[1] + tmp.y * data[5] + tmp.z * data[9],
			tmp.x * data[2] + tmp.y * data[6] + tmp.z * data[10]);
	}

	v3 m4::transformDirection(const v3 &vec) const
	{
		return v3(
			vec.x * data[0] + vec.y * data[1] + vec.z * data[2],
			vec.x * data[4] + vec.y * data[5] + vec.z * data[6],
			vec.x * data[8] + vec.y * data[9] + vec.z * data[10]);
	}

	v3 m4::transformInverseDirection(const v3 &vec) const
	{
		return v3(
			vec.x * data[0] + vec.y * data[4] + vec.z * data[8],
			vec.x * data[1] + vec.y * data[5] + vec.z * data[9],
			vec.x * data[2] + vec.y * data[6] + vec.z * data[10]);
	}

	v3 localToWorldDir(const v3 &local, const m4 &transform)
	{
		return transform.transformDirection(local);
	}

	v3 worldToLocalDir(const v3 &world, const m4 & transform)
	{
		return transform.transformInverseDirection(world);
	}

	v3 m4::operator* (const v3 & vec) const
	{
		return v3(
			vec.x * data[0] + vec.y * data[1] + vec.z * data[2] + data[3],
			vec.x * data[4] + vec.y * data[5] + vec.z * data[6] + data[7],
			vec.x * data[8] + vec.y * data[9] + vec.z * data[10] + data[11]);
	}

	m4 m4::operator* (const m4 & mat) const
	{
		m4 result;
		result.data[0] = (mat.data[0] * data[0]) + (mat.data[4] * data[1]) + (mat.data[8] * data[2]);
		result.data[4] = (mat.data[0] * data[4]) + (mat.data[4] * data[5]) + (mat.data[8] * data[6]);
		result.data[8] = (mat.data[0] * data[8]) + (mat.data[4] * data[9]) + (mat.data[8] * data[10]);

		result.data[1] = (mat.data[1] * data[0]) + (mat.data[5] * data[1]) + (mat.data[9] * data[2]);
		result.data[5] = (mat.data[1] * data[4]) + (mat.data[5] * data[5]) + (mat.data[9] * data[6]);
		result.data[9] = (mat.data[1] * data[8]) + (mat.data[5] * data[9]) + (mat.data[9] * data[10]);

		result.data[2] = (mat.data[2] * data[0]) + (mat.data[6] * data[1]) + (mat.data[10] * data[2]);
		result.data[6] = (mat.data[2] * data[4]) + (mat.data[6] * data[5]) + (mat.data[10] * data[6]);
		result.data[10] = (mat.data[2] * data[6]) + (mat.data[6] * data[9]) + (mat.data[10] * data[10]);

		result.data[3] = (mat.data[3] * data[0]) + (mat.data[6] * data[1]) + (mat.data[11] * data[2]);
		result.data[7] = (mat.data[3] * data[4]) + (mat.data[6] * data[5]) + (mat.data[11] * data[6]);
		result.data[11] = (mat.data[3] * data[6]) + (mat.data[6] * data[9]) + (mat.data[11] * data[10]);
			
		return result;
	}
}