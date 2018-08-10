#include "Links.h"

Links::Links()
{

}

Links::~Links()
{

}

double Links::currentLen() const
{
	v3 relativePos = particle[0]->pos - particle[1]->pos;
	return relativePos.len();
}

unsigned Cable::fillContact(ParticleCollision *contact, unsigned limit) const
{
	double length = currentLen();

	if (length < maxLen)
		return 0;

	contact->particle[0] = particle[0];
	contact->particle[1] = particle[1];

	v3 normal = particle[1]->pos - particle[0]->pos;
	normal.normalise();
	contact->contactNormal = normal;

	contact->penetration = length - maxLen;
	contact->restitution = restitution;

	return 1;
}

unsigned Rod::fillContact(ParticleCollision *contact, unsigned limit) const
{
	double currentLength = currentLen();

	if (currentLength == length)
		return 0;

	contact->particle[0] = particle[0];
	contact->particle[1] = particle[1];

	v3 normal = particle[1]->pos - particle[0]->pos;
	normal.normalise();

	if (currentLength > length)
	{
		contact->contactNormal = normal;
		contact->penetration = currentLength - length;
	}
	else
	{
		contact->contactNormal = normal * -1;
		contact->penetration = length - currentLength;
	}

	contact->restitution = 0;
	return 1;
}