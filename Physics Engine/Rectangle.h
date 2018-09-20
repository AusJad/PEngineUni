#pragma once

#include "Maths.h"
#include "RenderModuleStubb.h"
#include "Geometry3D.h"

struct BB {
	float minx, maxx, miny, maxy, minz, maxz;
};


namespace phys{
class Rectangle
{
public:
	Rectangle(vec3 c, float w, float h, float t);

	void update(float time, vec3 amount);

	void render();

	BB getBounds();

	const vec3 & getCenter() { return center; };

	float getHeight() { return height; }

	float getWidth() { return width; }

	float getThickness() { return thickness; }

	const OBB & getOBB() { return obb; }

	void orientate(const mat3 & toset) { obb.orientation = toset; }

private:
	vec3 center;
	float width;
	float height;
	float thickness;
	OBB obb;
};
};
