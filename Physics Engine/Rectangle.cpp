#include "Rectangle.h"

namespace phys {

	Rectangle::Rectangle(vec3 c, float w, float h, float t)
	{
		obb.position = physvec3(c.x(), c.y(), c.z());
		obb.size = physvec3(w, h, t);
	}

	void Rectangle::update(float time) {
		const float dampening = 0.99f;
		physvec3 acceleration = forceaccum * getInvMass();
		vel += acceleration * time;
		vel *= dampening;
		obb.position += vel * time;

		physvec3 angularAcceleration = MultiplyVector(torques, Inverse(intert_tensor));
		angularvel += angularAcceleration * time;
		angularvel *= dampening;
		
		orientation += angularvel * time;
		obb.orientation = Rotation3x3(RAD2DEG(orientation.x), RAD2DEG(orientation.y), RAD2DEG(orientation.z));
	}

	void Rectangle::addRotationalImpulse(physvec3 point, physvec3 impulse) {
		physvec3 torque = Cross(point - obb.position, impulse);
		physvec3 angularacel = MultiplyVector(torque, Inverse(intert_tensor));
		angularvel += angularacel;
	}

	void Rectangle::render() {
		glColor3f(.5, 0, 0);

		physvec3 rot = Decompose(obb.orientation);

		glPushMatrix();

		glTranslatef(obb.position.x, obb.position.y, obb.position.z);
		
		glRotatef(RAD2DEG(rot.x), 1, 0, 0);
		glRotatef(RAD2DEG(rot.y), 0, 1, 0);
		glRotatef(RAD2DEG(rot.z), 0, 0, 1);

		RNDR->DrawRect(vec3(), obb.size.x, obb.size.y, obb.size.z);

		glPopMatrix();
	}
	
	void Rectangle::applyForces() {
		forceaccum = GRAVITY * mass;
	}

	void Rectangle::addLinearImpulse(const physvec3 & impulse) {
		vel = vel + impulse;
	}

	float Rectangle::getInvMass() {
		if (mass == 0.0f) return 0;
		return 1.0f / mass;
	}
};