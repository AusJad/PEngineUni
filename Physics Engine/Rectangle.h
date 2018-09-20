#pragma once

#include "Maths.h"
#include "RenderModuleStubb.h"
#include "Geometry3D.h"

#define GRAVITY physvec3(0.0f, -9.8f, 0.0f)

namespace phys{
class Rectangle
{
public:
	Rectangle(vec3 c, float w, float h, float t);

	void update(float time);

	void render();

	const vec3 & getCenter() { return center; };

	float getHeight() { return height; }

	float getWidth() { return width; }

	float getThickness() { return thickness; }

	const OBB & getOBB() { return obb; }

	void orientate(const mat3 & toset) { obb.orientation = toset; }

	void applyForces();

	void addLinearImpulse(const physvec3 & impulse);

	float getInvMass();

	physvec3 vel, forceaccum;
	float mass;
	float COR;

private:
	vec3 center;
	float width;
	float height;
	float thickness;
	OBB obb;
};
};
