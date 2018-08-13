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

bool Collision::OBBOBB(const OBB &s1, const OBB &s2, collisionData *data)
{
	double dotprod;
	double s1minn1, s1maxn1, s2minn1, s2maxn1; // Shape 1 min value of normal 1
	v3 s1minn1c, s1maxn1c, s2minn1c, s2maxn1c; // Shape 1 min value of normal 1 coord

	for (int i = 0; i < s1.normals.size(); i++)
	{
		s1minn1 = s1.vertices[0].dot(s1.normals[i]);
		s1maxn1 = s1.vertices[0].dot(s1.normals[i]);

		for (int j = 1; j < s1.vertices.size(); j++)
		{
			dotprod = s1.vertices[j].dot(s1.normals[i]);

			if (dotprod < s1minn1)
			{
				s1minn1 = dotprod;
				s1minn1c = s1.vertices[j];
			}

			if (dotprod > s1maxn1)
			{
				s1maxn1 = dotprod;
				s1maxn1c = s1.vertices[j];
			}
		}

		s2minn1 = s2.vertices[0].dot(s1.normals[i]);
		s2maxn1 = s2.vertices[0].dot(s1.normals[i]);

		for (int j = 1; j < s2.vertices.size(); j++)
		{
			dotprod = s2.vertices[j].dot(s1.normals[i]);

			if (dotprod < s2minn1)
			{
				s2minn1 = dotprod;
				s2minn1c = s2.vertices[j];
			}

			if (dotprod > s2maxn1)
			{
				s2maxn1 = dotprod;
				s2maxn1c = s2.vertices[j];
			}
		}

		if (s1minn1 <= s2minn1 && s2minn1 <= s1maxn1 || s1minn1 <= s1minn1 && s1minn1 <= s2maxn1)
		{
			data->contactPoint = (s2maxn1c - s2minn1) + (s1maxn1c - s1minn1c);
		}
		else
			return false;
	}

	double s1minn2, s1maxn2, s2minn2, s2maxn2;
	v3 s1minn2c, s1maxn2c, s2minn2c, s2maxn2c;

	for (int i = 0; i < s2.normals.size(); i++)
	{
		s1minn2 = s1.vertices[0].dot(s2.normals[i]);
		s1minn2c = s1.vertices[0];
		s1maxn2 = s1.vertices[0].dot(s2.normals[i]);
		s1maxn2c = s1.vertices[0];

		for (int j = 1; j < s1.vertices.size(); j++)
		{
			dotprod = s1.vertices[j].dot(s2.normals[i]);

			if (dotprod < s1minn2)
			{
				s1minn2 = dotprod;
				s1minn2c = s1.vertices[j];
			}
				
			if (dotprod > s1maxn2)
			{
				s1maxn2 = dotprod;
				s1maxn2c = s1.vertices[j];
			}
		}

		s2minn2 = s2.vertices[0].dot(s2.normals[i]);
		s2maxn2 = s2.vertices[0].dot(s2.normals[i]);

		for (int j = 1; j < s2.vertices.size(); j++)
		{
			dotprod = s2.vertices[j].dot(s2.normals[i]);

			if (dotprod < s2minn2)
			{
				s2minn2 = dotprod;
				s2minn2c = s2.vertices[j];
			}

			if (dotprod > s2maxn2)
			{
				s2maxn2 = dotprod;
				s2maxn2c = s2.vertices[j];
			}
		}

		if (s1minn2 <= s2minn2 && s2minn2 <= s1maxn2 || s1minn2 <= s1minn2 && s1minn2 <= s2maxn2)
		{
			data->contactPoint = (s2maxn2c - s2minn2) + (s1maxn2c - s1minn2c);
		}
		else
			return false;
	}

	return true;
}