#pragma once

#include "v3.h"
#include <vector>

using namespace pys;

struct OBB
{
	std::vector<v3> vertices, normals;
	v3 max, min, CoM;
};

class sphere
{
public:
	v3 pos;
	double rad;

	void update();
};

struct collisionData
{
	sphere *boundingSpheres[2];
	v3 contactPoint;
	bool collided = false;
};

class Collision
{
public:
	bool sphereSphere(const sphere &s1, const sphere &s2, collisionData *data);

	void SATtest(const v3 &axis, std::vector<v3> vertices, double min, double max);
	bool OBBOBB(const OBB &s1, const OBB &s2);
	bool overlaps(double min1, double max1, double min2, double max2);
	bool isBetweenOrdered(double val, float lower, float upper);
};

