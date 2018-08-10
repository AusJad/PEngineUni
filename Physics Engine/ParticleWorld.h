#pragma once
#include "Particle.h"
#include "ParticleCollision.h"
#include "ForceGenerator.h"

using namespace pys;

class ParticleWorld
{
private:
	struct ParticleRegistration
	{
		Particle *particle;
		ParticleRegistration *next;
	};
	ParticleRegistration *firstParticle;

	ParticleForceRegistry registry;
	ParticleCollisionResolver resolver;

	struct CollisionGenRegistration
	{
		ParticleCollisionGenerator *gen;
		CollisionGenRegistration *next;
	};
	
	CollisionGenRegistration *firstCollisionGen;

	ParticleCollision *collisions;
	unsigned maxCollisions;

public:
	ParticleWorld::ParticleWorld(unsigned maxc, unsigned iterators = 0);

	void startFrame();

	unsigned generateCollision();
	void intergrate(double time);
	void runPhysics(double time);
};

class ParticleCollisionGenerator
{
public:
	virtual unsigned addCollision(ParticleCollision *collision, unsigned limit) const = 0;
};
