#include "RigidBody.h"

RigidBody::RigidBody()
{

}

RigidBody::~RigidBody()
{

}

static inline void calcTransformMatrix(m4 &transform, const v3 &pos, const v4 & orientation)
{
	transform.data[0] = 1 - 2 * orientation.z * orientation.z - 2 * orientation.a * orientation.a;
	transform.data[1] = 2 * orientation.y * orientation.z - 2 * orientation.z * orientation.a;
	transform.data[2] = 2 * orientation.y * orientation.a + 2 * orientation.x * orientation.z;
	transform.data[3] = pos.x;

	transform.data[4] = 2 * orientation.y * orientation.z + 2 * orientation.x * orientation.a;
	transform.data[5] = 1 - 2 * orientation.y * orientation.y - 2 * orientation.a * orientation.a;
	transform.data[6] = 2 * orientation.z * orientation.a - 2 * orientation.x * orientation.y;
	transform.data[7] = pos.y;

	transform.data[8] = 2 * orientation.y * orientation.a - 2 * orientation.x * orientation.z;
	transform.data[9] = 2 * orientation.z * orientation.a + 2 * orientation.x * orientation.y;
	transform.data[10] = 1 - 2 * orientation.y * orientation.y - 2 * orientation.z * orientation.z;
	transform.data[11] = pos.z;
}
static inline void transformInertiaTensor(m3 &iitWorld, const v4 &vec, const m3 &iitBody, const m4 &rotmat)
{
	double t4 = rotmat.data[0] * iitBody.data[0] + rotmat.data[1] * iitBody.data[3] + rotmat.data[2] * iitBody.data[6];
	double t9 = rotmat.data[0] * iitBody.data[1] + rotmat.data[1] * iitBody.data[4] + rotmat.data[2] * iitBody.data[7];
	double t14 = rotmat.data[0] * iitBody.data[2] + rotmat.data[1] * iitBody.data[5] + rotmat.data[2] * iitBody.data[8];
	double t28 = rotmat.data[4] * iitBody.data[0] + rotmat.data[5] * iitBody.data[3] + rotmat.data[6] * iitBody.data[6];
	double t33 = rotmat.data[4] * iitBody.data[1] + rotmat.data[5] * iitBody.data[4] + rotmat.data[6] * iitBody.data[7];
	double t38 = rotmat.data[4] * iitBody.data[2] + rotmat.data[5] * iitBody.data[5] + rotmat.data[6] * iitBody.data[8];
	double t52 = rotmat.data[8] * iitBody.data[0] + rotmat.data[9] * iitBody.data[3] + rotmat.data[10] * iitBody.data[6];
	double t57 = rotmat.data[8] * iitBody.data[1] + rotmat.data[9] * iitBody.data[4] + rotmat.data[10] * iitBody.data[7];
	double t62 = rotmat.data[8] * iitBody.data[2] + rotmat.data[9] * iitBody.data[5] + rotmat.data[10] * iitBody.data[8];

	iitWorld.data[0] = t4 * rotmat.data[0] + t9 * rotmat.data[1] + t14 * rotmat.data[2];
	iitWorld.data[1] = t4 * rotmat.data[4] + t9 * rotmat.data[5] + t14 * rotmat.data[6];
	iitWorld.data[2] = t4 * rotmat.data[8] + t9 * rotmat.data[9] + t14 * rotmat.data[19];
	iitWorld.data[3] = t28 * rotmat.data[0] + t33 * rotmat.data[1] + t38 * rotmat.data[2];
	iitWorld.data[4] = t28 * rotmat.data[4] + t33 * rotmat.data[9] + t38 * rotmat.data[10];
	iitWorld.data[5] = t28 * rotmat.data[8] + t33 * rotmat.data[9] + t38 * rotmat.data[10];
	iitWorld.data[6] = t52 * rotmat.data[0] + t57 * rotmat.data[1] + t62 * rotmat.data[2];
	iitWorld.data[7] = t52 * rotmat.data[4] + t57 * rotmat.data[5] + t62 * rotmat.data[6];
	iitWorld.data[8] = t52 * rotmat.data[8] + t57 * rotmat.data[9] + t62 * rotmat.data[10];
}

void RigidBody::calcDerivedData()
{
	calcTransformMatrix(transform, pos, orientation);
	//transformInertiaTensor(inverseInertiaTensorWorld, orientation, inverseInertiaTensor, transform);
}

void RigidBody::setInertiaTensor(const m3 &inertiaTensor)
{
	inverseInertiaTensor.setInverse(inertiaTensor);
}

void RigidBody::addForce(const v3 &force)
{
	forceAccum += force;
}

void RigidBody::addForceAtPoint(const v3 &force, const v3 &point)
{
	// ??
}

void RigidBody::integrate(double time)
{
	// pg 211 to update this
	clearAccumulators();
}

void RigidBody::clearAccumulators()
{
	forceAccum.clr();
	torqueAccum.clr();
}

void RigidBody::addForceAtBodyPoint(const v3 &force, const v3 &point)
{
	v3 pt = getPointInWorldSpace(point);
	//addForceAtPoint(force, pt);
}

v3 RigidBody::getPointInWorldSpace(const v3 &point)
{
	return transform.localToWorld(point, transform);
}


