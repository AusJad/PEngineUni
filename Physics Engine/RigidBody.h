#pragma once
#include "Geometry3D.h"
#include <vector>

// each object has a rigid body
// each object (say a chair) can have multiple bounding boxes
// store each box in a vector

class RigidBody
{
public:
	RigidBody();
	~RigidBody();

	void addAABB(const AABB & box);
	void addAABB(const physvec3 & pos, const physvec3 halfSize);
	void addOBB(const OBB & box);
	void addOBB(const physvec3 & pos, const physvec3 halfSize, const mat3 orientation);

private:
	std::vector<AABB> aabb;
	std::vector<OBB> obb;
};

