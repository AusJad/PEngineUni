#include "Collision.h"

void sphere::update()
{
	// Physics update happens here
}

bool Collision::sphereSphere(const sphere &s1, const sphere &s2, collisionData *data)
{
	if (!data->collided)
	{
		sphere nOne, nTwo;
		nOne = s1;
		nTwo = s2;

		nOne.update();
		nTwo.update();

		double distance = (nTwo.pos - nOne.pos).magnitude();
		if (distance <= nOne.rad + nTwo.rad)
		{
			data->collided = true;
			data->contactPoint = s1.pos - s2.pos;
		}

		return false;
	}

	data->collided = false;
	return true;
}

void Collision::SATtest(const v3 &axis, std::vector<v3> vertices, double min, double max)
{
	for (int i = 0; i < vertices.size(); i++)
	{
		double dotprod = vertices[i].dot(axis);

		if (dotprod < min)
			min = dotprod;
		if (dotprod > max)
			max = dotprod;
		// need to return min + max
	}
}

bool Collision::OBBOBB(const OBB &s1, const OBB &s2)
{
	// Default first value.
	double s1minn1 = s1.vertices[0].dot(s1.normals[0]); // Shape 1 min for normal of s1
	double s1maxn1 = s1.vertices[0].dot(s1.normals[0]);
	double s2minn1 = s2.vertices[0].dot(s1.normals[0]);
	double s2maxn1 = s2.vertices[0].dot(s1.normals[0]);

	// Loop through remaining normals and find mins and maxes.
	for (int i = 1; i < s1.normals.size(); i++)
	{
		SATtest(s1.normals[i], s1.vertices, s1minn1, s1maxn1);
		SATtest(s1.normals[i], s2.vertices, s2minn1, s2maxn1);

		if (!overlaps(s1minn1, s1maxn1, s2minn1, s2maxn1))
			return false;
	}

	// Default first value.
	double s1minn2 = s1.vertices[0].dot(s2.normals[0]); // Shape 1 min for normal of s2
	double s1maxn2 = s1.vertices[0].dot(s2.normals[0]);
	double s2minn2 = s2.vertices[0].dot(s2.normals[0]);
	double s2maxn2 = s2.vertices[0].dot(s2.normals[0]);
	
	for (int i = 1; i < s2.normals.size(); i++)
	{
		SATtest(s2.normals[i], s1.vertices, s1minn2, s1maxn2);
		SATtest(s2.normals[i], s2.vertices, s2minn2, s2maxn2);

		if (!overlaps(s1minn2, s1maxn2, s2minn2, s2maxn2))
			return false;
	}

	return true;
}

bool Collision::overlaps(double min1, double max1, double min2, double max2)
{
	return isBetweenOrdered(min2, min1, max1) || isBetweenOrdered(min1, min2, max2);
}

bool Collision::isBetweenOrdered(double val, float lower, float upper)
{
	return lower <= val && val <= upper;
}