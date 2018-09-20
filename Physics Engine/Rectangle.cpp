#include "Rectangle.h"

namespace phys {

	Rectangle::Rectangle(vec3 c, float w, float h, float t)
	{
		obb.position = physvec3(c.x(), c.y(), c.z());
		obb.size = physvec3(w, h, t);
		std::cout << obb.size << std::endl;
	}

	void Rectangle::update(float time, vec3 amount) {
		obb.position += physvec3((amount * time).x(), (amount * time).y(), (amount * time).z());
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

	BB Rectangle::getBounds() {
		BB ret;

		ret.maxx = center.x() + width;
		ret.minx = center.x() - width;
		ret.maxy = center.y() + width;
		ret.miny = center.y() - width;
		ret.maxz = center.z() + width;
		ret.minz = center.z() - width;

		return ret;
	}

};