#include "ForceGenerator.h"

using namespace pys;

/* PARTICLE FORCE REGISTRY START */
void ParticleForceRegistry::add(Particle* part, ForceGenerator *nfg)
{
	ParticleForceRegistration tmp;
	tmp.particle = part;
	tmp.fg = nfg;

	reg.push_back(tmp);
}

void ParticleForceRegistry::remove(Particle* part, ForceGenerator *nfg)
{
	//comp overloads required here
}

void ParticleForceRegistry::clear()
{
	reg.clear();
}

void ParticleForceRegistry::updateForces(double time)
{
	registry::iterator i = reg.begin();
	for (; i != reg.end(); i++)
		i->fg->updateForce(i->particle, time);
}
/* PARTICLE FORCE REGISTRY END */

/* PARTICLE GRAVITY START */
ParticleGravity::ParticleGravity(const v3 &grav)
{
	gravity = grav;
}

void ParticleGravity::updateForce(Particle *part, double time)
{
	if (!part->hasMass()) return;

	part->addForce(gravity * (1 / part->invm)); // invm mass?
}
/* PARTICLE GRAVITY END */

/* PARTICLE DRAG START */
ParticleDrag::ParticleDrag(double dragco, double sqdragco)
{
	k1 = dragco;
	k2 = sqdragco;
}

void ParticleDrag::updateForce(Particle *part, double time)
{
	v3 force = part->vel;

	double dragCoeff = force.len();
	dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

	force.normalise();
	force *= -dragCoeff;
	part->addForce(force);
}
/* PARTICLE DRAG END */

/* PARTICLE SPRING START */
ParticleSpring::ParticleSpring(Particle *o, double sc, double rl)
{
	other = o;
	sc = springConst;
	rl = restLen;
}

void ParticleSpring::updateForce(Particle* part, double time)
{
	v3 force = part->vel;
	force -= other->vel;

	double mag = force.len();
	mag -= restLen;

	force.normalise();
	force *= -mag;
	part->addForce(force);
}
/* PARTICLE SPRING END */

/* ANCHORED SPRING START */
AnchoredSpring::AnchoredSpring(v3* anc, double sc, double rl)
{
	anchor = anc;
	springConst = sc;
	restLen = rl;
}

void AnchoredSpring::updateForce(Particle *part, double time)
{
	v3 force = part->vel;
	force -= *anchor;

	double mag = force.len();
	mag -= restLen;
	mag *= springConst;

	force.normalise();
	force *= -mag;
	part->addForce(force);
}
/* ANCHORED SPRING END */

/* BUNGEE START */
Bungee::Bungee(Particle *o, double sc, double rl)
{
	other = o;
	springConst = sc;
	restLen = rl;
}

void Bungee::updateForce(Particle *part, double time)
{
	v3 force = part->vel;
	force -= other->vel;

	double mag = force.len();
	if (mag <= restLen) return;

	force.normalise();
	force *= -mag;
	part->addForce(force);
}
/* BUNGEE END */

/* BUOYANCY START */
Buoyancy::Buoyancy(double md, double vol, double wh, double ld)
{
	maxDepth = md;
	volume = vol;
	waterHeight = wh;
	liquidDensity = ld;
}

Buoyancy::Buoyancy(const v3 &cofb, double md, double vol, double wh, double density)
{
	centerOfBuoyancy = cofb;
	maxDepth = md;
	volume = vol;
	waterHeight = wh;
	density = liquidDensity;
}

void Buoyancy::updateForce(Particle *part, double time)
{
	double depth = part->pos.y;

	if (depth >= waterHeight + maxDepth) return;

	v3 force(0, 0, 0);

	if (depth <= waterHeight - maxDepth)
	{
		force.y = liquidDensity * volume;
		part->addForce(force);
		return;
	}

	force.y = liquidDensity * volume * (depth - maxDepth - waterHeight) / 2 * maxDepth;
	part->addForce(force);
}

void Buoyancy::updateForces(RigidBody *body, double time)
{
	double depth = body->pos.y;
	
	if (depth >= waterHeight + maxDepth) return;

	v3 force(0, 0, 0);

	if (depth <= waterHeight - maxDepth)
	{
		force.y = liquidDensity * volume;
		body->addForce(force);
		return;
	}

	force.y = liquidDensity * volume * (depth - maxDepth - waterHeight) / 2 * maxDepth;
	body->addForce(force);
}
/* BUOYANCY END */

/* GRAVITY START */
Gravity::Gravity(const v3 &grav)
{
	gravity = grav;
}

void Gravity::updateForce(RigidBody *body, double time)
{
	if (!body->inverseMass)
		return;
	body->addForce(gravity * (1 / body->inverseMass));
}
/* GRAVITY END */

/* SPRING START */
Spring::Spring(const v3 & localConnectionPt, RigidBody *o, const v3 &otherCPt, double springConst, double rl)
{
	connectionPoint = localConnectionPt;
	otherCP = otherCPt;
	other = o;
	springConstant = springConst;
	restLen = rl;
}

void Spring::updateForce(RigidBody *body, double time)
{
	v3 lws = body->getPointInWorldSpace(connectionPoint);
	v3 ows = other->getPointInWorldSpace(otherCP);

	v3 force = lws - ows;

	double mag = force.len();
	mag -= restLen;
	mag *= springConstant;

	force.normalise();
	force *= -mag;
	body->addForceAtPoint(force, lws);
}
/* SPRING END */