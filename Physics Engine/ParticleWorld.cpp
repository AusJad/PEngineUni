#include "ParticleWorld.h"

void ParticleWorld::startFrame()
{
	ParticleRegistration *reg = firstParticle;
	while (reg)
	{
		reg->particle->frc_accum.clr();
		reg = reg->next;
	}
}

unsigned ParticleWorld::generateCollision()
{
	unsigned limit = maxCollisions;
	ParticleCollision * nextCollision = collisions;

	CollisionGenRegistration *reg = firstCollisionGen;
	while (reg)
	{
		unsigned used = reg->gen->addCollision(nextCollision, limit);
		limit -= used;
		nextCollision += used;

		if (limit <= 0)
			break;

		reg = reg->next;
	}

	return maxCollisions - limit;
}

void ParticleWorld::intergrate(double time)
{
	ParticleRegistration *reg = firstParticle;
	while (reg)
	{
		reg->particle->update(time);
		reg = reg->next;
	}
}

void ParticleWorld::runPhysics(double time)
{
	registry.updateForces(time);
	intergrate(time);
	unsigned usedCollisions = generateCollision();
	
	if (resolver.getIter()) // if (calculateIterations) in book
		resolver.setIt(usedCollisions * 2);

	resolver.resolveCollisions(collisions, usedCollisions, time);
}