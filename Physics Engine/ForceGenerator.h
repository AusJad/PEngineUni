#pragma once

#include "Particle.h"

namespace pys {
	class ForceGenerator
	{
	public:
		virtual void updateForce(Particle & toupdate, double time) = 0;
	};

	class ParticleGravity : public ForceGenerator {
		public:
			void updateForce(Particle & toupdate, double time) {
				if (!toupdate.hasMass()) return;

				toupdate.addForce(grav * toupdate.invm);
			}

		private:
			v3 grav;
	};

	class ParticleDrag : public ForceGenerator {
		public:
			void updateForce(Particle & toupdate, double time) {
				v3 force = toupdate.vel;

				double drag = force.len();
				drag = k1 * drag + k2 * drag * drag;

				force.normalise();

				force *= -drag;

				toupdate.addForce(force);
			}
		private:
			double k1, k2;
	};

}

