#pragma once
#include "Particle.h"
#include "RigidBody.h"
#include <vector>

namespace pys
{
	class ForceGenerator
	{
	public:
		virtual void updateForce(Particle *particle, double time) = 0;
		virtual void updateForce(RigidBody *body, double time) = 0;
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class ParticleForceRegistry
	{
	protected:
		struct ParticleForceRegistration
		{
			Particle *particle;
			ForceGenerator *fg;
		};

		typedef std::vector<ParticleForceRegistration> registry;
		registry reg;

	public:
		void add(Particle* part, ForceGenerator *nfg);
		void remove(Particle* part, ForceGenerator *nfg);
		void clear();
		void updateForces(double time);
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class ParticleGravity : public ForceGenerator
	{
	private:
		v3 gravity;
	public:
		ParticleGravity(const v3 &grav);

		virtual void updateForce(Particle *part, double time);
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class ParticleDrag : public ForceGenerator
	{
	private:
		double k1, k2;
	public:
		ParticleDrag(double dragco, double sqdragco);
		virtual void updateForce(Particle *part, double time);
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class ParticleSpring : public ForceGenerator
	{
	private:
		Particle *other;
		double springConst, restLen;
	public:
		ParticleSpring(Particle *o, double sc, double rl);
		virtual void updateForce(Particle* part, double time);
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class AnchoredSpring : public ForceGenerator
	{
	private:
		v3 *anchor;
		double springConst, restLen;
	public:
		AnchoredSpring(v3* anc, double sc, double rl);
		virtual void updateForce(Particle *part, double time);
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Bungee : public ForceGenerator
	{
	private:
		Particle *other;
		double springConst, restLen;
	public:
		Bungee(Particle *o, double sc, double rl);
		virtual void updateForce(Particle *part, double time);
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Buoyancy : public ForceGenerator
	{
	private:
		double maxDepth, volume, waterHeight, liquidDensity;
		v3 centerOfBuoyancy;
	public:
		Buoyancy(double md, double vol, double wh, double ld);
		Buoyancy(const v3 &cofb, double md, double vol, double wh, double density);
		virtual void updateForce(Particle *part, double time);
		virtual void updateForces(RigidBody *body, double time);
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Gravity : public ForceGenerator
	{
	private:
		v3 gravity;
	public:
		Gravity(const v3 &grav);
		virtual void updateForce(RigidBody *body, double time);
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Spring : public ForceGenerator
	{
	private:
		v3 connectionPoint, otherCP;
		RigidBody *other;
		double springConstant, restLen;
	public:
		Spring(const v3 & localConnectionPt, RigidBody *o, const v3 &otherCPt, double springConst, double rl);
		virtual void updateForce(RigidBody *body, double time);
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////
}

