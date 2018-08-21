#include "Collision.h"

void sphere::update()
{
	pos += phys.velo;
}

sphere::sphere()
{
	rad = 0;
	pos = vec3(0, 0, 0);
}

sphere::sphere(vec3 p, double r, physVar ph)
{
	pos = p;
	rad = r;
	phys = ph;
}

OBB::OBB()
{
	pos = vec3(0, 0, 0);
	CoM = vec3(0, 0, 0);
	min = vec3(0, 0, 0);
	max = vec3(0, 0, 0);
	vertices.clear();
	normals.clear();
}

// For now OBB is created with position coords in real world being the same coord that the CoM is at.
// This can cause issues if the CoM is off to one side meaning that the box will be as big as greatest distance from CoM to each edge.
OBB::OBB(vec3 position, double width, float height, float depth, physVar p)
{
	pos = position;
	CoM = position;
	phys = p;

	vertices.clear();
	vertices.push_back(vec3(pos.x() - width / 2, pos.y() + height / 2, pos.z() + depth / 2)); // Front top left
	vertices.push_back(vec3(pos.x() - width / 2, pos.y() - height / 2, pos.z() + depth / 2)); // Front bottom left
	vertices.push_back(vec3(pos.x() + width / 2, pos.y() - height / 2, pos.z() + depth / 2)); // Front bottom right
	vertices.push_back(vec3(pos.x() + width / 2, pos.y() + height / 2, pos.z() + depth / 2)); // Front top right

	vertices.push_back(vec3(pos.x() - width / 2, pos.y() + height / 2, pos.z() - depth / 2)); // Back top left
	vertices.push_back(vec3(pos.x() - width / 2, pos.y() - height / 2, pos.z() - depth / 2)); // Back bottom left
	vertices.push_back(vec3(pos.x() + width / 2, pos.y() - height / 2, pos.z() - depth / 2)); // Back bottom right
	vertices.push_back(vec3(pos.x() + width / 2, pos.y() + height / 2, pos.z() - depth / 2)); // Back top right

	vec3 temp;
	for (int i = 0; i < vertices.size(); i++)
	{
		temp = vertices[i];
		temp.normailse();
		normals.push_back(temp);
	}

	// TMP SOLUTION
	min = vec3(0, 0, 0);
	max = vec3(0, 0, 0);
}

OBB::OBB(vec3 position, float width, float height, float depth)
{
	pos = position;
	CoM = position;

	vertices.clear();
	vertices.push_back(vec3(pos.x() - width / 2, pos.y() - height / 2, pos.z() + depth / 2)); // Front bottom left
	vertices.push_back(vec3(pos.x() - width / 2, pos.y() + height / 2, pos.z() + depth / 2)); // Front top left
	vertices.push_back(vec3(pos.x() + width / 2, pos.y() + height / 2, pos.z() + depth / 2)); // Front top right
	vertices.push_back(vec3(pos.x() + width / 2, pos.y() - height / 2, pos.z() + depth / 2)); // Front bottom right
	vertices.push_back(vec3(pos.x() - width / 2, pos.y() - height / 2, pos.z() - depth / 2)); // Back bottom left
	vertices.push_back(vec3(pos.x() - width / 2, pos.y() + height / 2, pos.z() - depth / 2)); // Back top left
	vertices.push_back(vec3(pos.x() + width / 2, pos.y() + height / 2, pos.z() - depth / 2)); // Back top right
	vertices.push_back(vec3(pos.x() + width / 2, pos.y() - height / 2, pos.z() - depth / 2)); // Back bottom right

	vec3 temp;
	for (int i = 0; i < vertices.size(); i++)
	{
		temp = vertices[i];
		temp.normailse();
		normals.push_back(temp);
	}
}

void OBB::update()
{
	pos += phys.velo;
	CoM += phys.velo;

	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i] += phys.velo;
	}
}

bool sphere::sphereSphere(const sphere &s, collisionData *data)
{
	if (!data->collided)
	{
		sphere nOne, nTwo;

		nOne.pos = pos;
		nOne.rad = rad;
		nOne.phys = phys;

		nTwo = s;

		nOne.update();
		nTwo.update();

		float distance = (nTwo.pos - nOne.pos).magnitude();
		if (distance <= nOne.rad + nTwo.rad)
		{
			data->collided = true;
			data->contactPoint = pos - s.pos;
		}

		return false;
	}

	data->collided = false;
	return true;
}

bool OBB::OBBOBB(const OBB &s, collisionData *data)
{
	float dotprod;
	float s1minn1, s1maxn1, s2minn1, s2maxn1; // Shape 1 min value of normal 1
	vec3 s1minn1c, s1maxn1c, s2minn1c, s2maxn1c; // Shape 1 min value of normal 1 coord

	for (int i = 0; i < normals.size(); i++)
	{
		s1minn1 = vertices[0].dot(normals[i]);
		s1maxn1 = vertices[0].dot(normals[i]);

		for (int j = 1; j < vertices.size(); j++)
		{
			dotprod = vertices[j].dot(normals[i]);

			if (dotprod < s1minn1)
			{
				s1minn1 = dotprod;
				s1minn1c = vertices[j];
			}

			if (dotprod > s1maxn1)
			{
				s1maxn1 = dotprod;
				s1maxn1c = vertices[j];
			}
		}

		s2minn1 = s.vertices[0].dot(normals[i]);
		s2maxn1 = s.vertices[0].dot(normals[i]);

		for (int j = 1; j < s.vertices.size(); j++)
		{
			dotprod = s.vertices[j].dot(normals[i]);

			if (dotprod < s2minn1)
			{
				s2minn1 = dotprod;
				s2minn1c = s.vertices[j];
			}

			if (dotprod > s2maxn1)
			{
				s2maxn1 = dotprod;
				s2maxn1c = s.vertices[j];
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
	vec3 s1minn2c, s1maxn2c, s2minn2c, s2maxn2c;

	for (int i = 0; i < s.normals.size(); i++)
	{
		s1minn2 = vertices[0].dot(s.normals[i]);
		s1minn2c = vertices[0];
		s1maxn2 = vertices[0].dot(s.normals[i]);
		s1maxn2c = vertices[0];

		for (int j = 1; j < vertices.size(); j++)
		{
			dotprod = vertices[j].dot(s.normals[i]);

			if (dotprod < s1minn2)
			{
				s1minn2 = dotprod;
				s1minn2c = vertices[j];
			}
				
			if (dotprod > s1maxn2)
			{
				s1maxn2 = dotprod;
				s1maxn2c = vertices[j];
			}
		}

		s2minn2 = s.vertices[0].dot(s.normals[i]);
		s2maxn2 = s.vertices[0].dot(s.normals[i]);

		for (int j = 1; j < s.vertices.size(); j++)
		{
			dotprod = s.vertices[j].dot(s.normals[i]);

			if (dotprod < s2minn2)
			{
				s2minn2 = dotprod;
				s2minn2c = s.vertices[j];
			}

			if (dotprod > s2maxn2)
			{
				s2maxn2 = dotprod;
				s2maxn2c = s.vertices[j];
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