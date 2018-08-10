#pragma once

#include "Particle.h"

namespace pys
{
	class ParticleCollision
	{
	public:
		Particle *particle[2];
		double restitution;
		v3 contactNormal;
		double penetration;

		ParticleCollision();
		~ParticleCollision();

		void resolve(double time);
		double calcSeparatingVelo() const;

	private:
		void resolveVelo(double time);
		void resolveInterpenetration(double time);
	};

	class ParticleCollisionResolver
	{
	protected:
		unsigned i, iUsed;
	public:
		unsigned getIter() const;
		ParticleCollisionResolver(unsigned it);
		void setIt(unsigned it);
		void resolveCollisions(ParticleCollision *contactArray, unsigned numContacts, double time);
	};
}