#pragma once

#include "v3.h"

namespace pys {
	class Particle
	{
	public:
		v3 pos;
		v3 vel;
		v3 acc;
		v3 frc_accum;
		double drag;
		double invm;

		Particle() {
			drag = 0;
			invm = 0;
		}

		Particle(const v3 & pos, const v3 & vel, const v3 & acc, double drag, double invm) {
			this-> pos = pos;
			this->vel = vel;
			this->acc = acc;
			this->drag = drag;
			this->invm = invm;
		}

		void addForce(const v3 & toadd) {
			frc_accum += toadd;
		}

		bool hasMass() {
			return invm != 0;
		}

		void update(double time) {
			pos += vel * time;

			v3 res_accel = acc;
			res_accel += frc_accum * invm;

			vel += res_accel * time;

			vel *= powf(drag, time);
			
			frc_accum.clr();
		}
	};
}

