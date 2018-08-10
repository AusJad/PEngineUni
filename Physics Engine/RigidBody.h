#pragma once

#include "v3.h"
#include "v4.h"
#include "m4.h"
#include "m3.h"

using namespace pys;

class RigidBody
{
public:
	RigidBody();
	~RigidBody();

	void calcDerivedData();
	void setInertiaTensor(const m3 & inertiaTensor);
	void addForce(const v3 &force);
	void addForceAtPoint(const v3 &force, const v3 &point);
	void integrate(double time);
	void addForceAtBodyPoint(const v3 &force, const v3 &point);
	v3 getPointInWorldSpace(const v3 &point);
	void clearAccumulators();

	double inverseMass, angularDamping;
	v3 pos, velo, rot, forceAccum, torqueAccum;
	v4 orientation;
	m4 transform;
	m3 inverseInertiaTensor;

};


