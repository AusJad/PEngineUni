#include "RigidBody.h"


RigidBody::RigidBody()
{

}


RigidBody::~RigidBody()
{

}

void RigidBody::addAABB(const AABB & box)
{
	aabb.push_back(box);
}

void RigidBody::addAABB(const physvec3 & pos, const physvec3 halfSize)
{
	aabb.push_back(AABB(pos, halfSize));
}

void RigidBody::addOBB(const OBB & box)
{
	obb.push_back(box);
}

void RigidBody::addOBB(const physvec3 & pos, const physvec3 halfSize, const mat3 orientation)
{
	obb.push_back(OBB(pos, halfSize, orientation));
}

