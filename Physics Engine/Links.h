#pragma once
#include "Particle.h"
#include "ParticleCollision.h"

using namespace pys;
class Links
{
public:
	Links();
	~Links();

	double currentLen() const;
	virtual unsigned fillContact(ParticleCollision *contact, unsigned limit) const = 0;

protected:
	Particle * particle[2];
};

class Cable : public Links
{
private:
	double maxLen, restitution;
public:
	virtual unsigned fillContact(ParticleCollision * contact, unsigned limit) const;
};

class Rod : public Links
{
private:
	double length;
public:
	virtual unsigned fillContact(ParticleCollision *contact, unsigned limit) const;
};

