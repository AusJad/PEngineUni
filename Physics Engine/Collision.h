#pragma once

#include "Maths.h"
#include <vector>

// Note problem here as nothing links to the two collider objects.
struct collisionData
{
	vec3 contactPoint;
	bool collided;

	collisionData()
	{
		contactPoint = vec3(0, 0, 0);
		collided = false;
	}
};

struct physVar
{
	vec3 velo;

	physVar()
	{
		velo.sx(0);
		velo.sy(0);
		velo.sz(0);
	}

	physVar(float x, float y, float z)
	{
		velo.sx(x);
		velo.sy(y);
		velo.sz(z);
	}
};

class OBB
{
public:
	OBB();
	OBB(vec3 position, double width, float height, float depth, physVar p);
	OBB(vec3 position, float width, float height, float depth);

	std::vector<vec3> vertices, normals;
	vec3 max, min, CoM; // Using its own coord system.
	vec3 pos; // Using world coord system.
	// may need some conversion variables to move from personal coord system to world coord system.

	physVar phys; // Temp.

	void update();

	bool OBBOBB(const OBB &s, collisionData *data);
};

class sphere
{
public:
	sphere();
	sphere(vec3 p, double r, physVar ph);

	vec3 pos;
	float rad;

	physVar phys; // Temp.

	void update();

	bool sphereSphere(const sphere &s, collisionData *data);
};
