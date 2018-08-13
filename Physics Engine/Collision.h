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
	v3 contactPoint;
	bool collided = false;
};


class Collision
{
public:
	static bool sphereSphere(const sphere &s1, const sphere &s2, collisionData *data);

	bool OBBOBB(const OBB &s1, const OBB &s2, collisionData *data);
};

