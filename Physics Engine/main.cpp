// Physics Engine.cpp : Defines the entry point for the console application.
//

#include "RenderModuleStubb.h"
#include "camera.h"
#include "Particle.h"
#include "Rectangle.h"

//Basic engine setup
#if true

Camera Cam(vec3(-.5, 0, 0));

phys::Rectangle rect(vec3(9, 1, 1), 3, 2, 2);

phys::Rectangle rect2(vec3(3, 1, 1), 2, 2, 2);

double prevx = -1, prevy = -1;

float ttime = 0;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void mouseCallback(GLFWwindow* window, double x, double y);

#endif


void updateAngularImpulse(phys::Rectangle & r1, phys::Rectangle & r2, CollisionManifold & CM, int c) {

	if (r1.getInvMass() + r2.getInvMass() == 0.0f) {
		return;
	}

	physvec3 rc1 = CM.contacts[c] - r1.getOBB().position;
	physvec3 rc2 = CM.contacts[c] - r2.getOBB().position;

	physmat4 i1 = Inverse(r1.intert_tensor);
	physmat4 i2 = Inverse(r2.intert_tensor);

	physvec3 relvel = (r2.vel + Cross(r2.angularvel, rc2))
		- (r1.vel + Cross(r1.angularvel, rc1));

	physvec3 relnorm = CM.normal;

	Normalize(relnorm);

	if (Dot(relvel, relnorm) > 0.0f) {
		return;
	}

	float e = fminf(r1.COR, r2.COR);
	float numerator = (-(1.0f + e) * Dot(relvel, relnorm));
	float d1 = r1.getInvMass() + r2.getInvMass();
	physvec3 d2 = Cross(MultiplyVector(Cross(rc1, relnorm), i1), rc1);
	physvec3 d3 = Cross(MultiplyVector(Cross(rc2, relnorm), i2), rc2);

	float denom = d1 + Dot(relnorm, d2 + d3);
	float j = (denom == 0.0f) ? 0.0f : numerator / denom;

	if (CM.contacts.size() > 0 && j != 0.0f) {
		j /= (float)CM.contacts.size();
	}

	physvec3 impulse = relnorm * j;

	std::cout << j << std::endl;
	r1.vel -= impulse * r1.getInvMass();
	r2.vel += impulse * r2.getInvMass();
	r1.angularvel -= MultiplyVector(Cross(rc1, impulse), i1);
	r2.angularvel += MultiplyVector(Cross(rc2, impulse), i2);

	}

	void physUpdate(phys::Rectangle & r1, phys::Rectangle & r2) {
		r1.update(ttime);
		r2.update(ttime);

		if (OBBOBB(r1.getOBB(), r2.getOBB())) {
			CollisionManifold coll = FindCollisionFeatures(r1.getOBB(), r2.getOBB());
			if (coll.colliding) {
					for (unsigned i = 0; i < coll.contacts.size(); i++)
						updateAngularImpulse(r1, r2, coll, 0);
			}
		}

}

void init() {
		rect.mass = 5;
		rect2.mass = 5;
		rect.COR = .5;
		rect2.COR = .5;

		rect2.vel = physvec3(5, 0, 0);
		rect.vel = physvec3(-5, 0, 0);

		float frac = 1 / 12;
		rect2.intert_tensor._11 = (pow(rect2.getOBB().size.y, 2) + pow(rect2.getOBB().size.z, 2)) * rect2.mass * frac;
		rect2.intert_tensor._22 = (pow(rect2.getOBB().size.x, 2) + pow(rect2.getOBB().size.z, 2)) * rect2.mass * frac;
		rect2.intert_tensor._33 = (pow(rect2.getOBB().size.x, 2) + pow(rect2.getOBB().size.y, 2)) * rect2.mass * frac;
		rect2.intert_tensor._44 = 1.0f;

		rect.intert_tensor._11 = (pow(rect.getOBB().size.y, 2) + pow(rect.getOBB().size.z, 2)) * rect.mass * frac;
		rect.intert_tensor._22 = (pow(rect.getOBB().size.x, 2) + pow(rect.getOBB().size.z, 2)) * rect.mass * frac;
		rect.intert_tensor._33 = (pow(rect.getOBB().size.x, 2) + pow(rect.getOBB().size.y, 2)) * rect.mass * frac;
		rect.intert_tensor._44 = 1.0f;

		rect.orientation = physvec3(DEG2RAD(45), 0, 0);
	}

	int main()
	{
		init();
		RNDR->init(0, NULL);

		glfwSetKeyCallback(RNDR->getWindow(), keyCallback);
		glfwSetCursorPosCallback(RNDR->getWindow(), mouseCallback);

		while (true) {
			Cam.update(ttime);

			physUpdate(rect, rect2);

			RNDR->startRenderCycle();

			//Draw Suff here!!!!
			rect.render();
			rect2.render();

			Cam.render();
			RNDR->endRenderCycle();

			//ttime: holds time since last update
			ttime = 0.016;
		}

		return 0;
	}

	//Callbacks
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_W && action == GLFW_PRESS) {
			Cam.moveForward = true;
		}
		else
			if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
				Cam.moveForward = false;
			}
			else
				if (key == GLFW_KEY_S && action == GLFW_PRESS) {
					Cam.moveBack = true;
				}
				else
					if (key == GLFW_KEY_S  && action == GLFW_RELEASE) {
						Cam.moveBack = false;
					}
					else
						if (key == GLFW_KEY_D && action == GLFW_PRESS) {
							Cam.moveRight = true;
						}
						else
							if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
								Cam.moveRight = false;
							}
							else
								if (key == GLFW_KEY_A && action == GLFW_PRESS) {
									Cam.moveLeft = true;
								}
								else
									if (key == GLFW_KEY_A  && action == GLFW_RELEASE) {
										Cam.moveLeft = false;
									}
		if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
			Cam.lookUp = true;
		}
		else
			if (key == GLFW_KEY_Q && action == GLFW_RELEASE) {
				Cam.lookUp = false;
			}
			else
				if (key == GLFW_KEY_E && action == GLFW_PRESS) {
					Cam.lookDown = true;
				}
				else
					if (key == GLFW_KEY_E  && action == GLFW_RELEASE) {
						Cam.lookDown = false;
					}
	}

	void mouseCallback(GLFWwindow* window, double x, double y) {

		if (prevx == -1) prevx = x;
		if (prevy == -1) prevy = y;

		Cam.horizontalAngle -= (prevx - x) * ttime * Cam.rotateSpeed;

		Cam.verticalAngle -= (prevy - y) * ttime * Cam.rotateSpeed;
		if (Cam.verticalAngle <= Cam.maxNangle && (prevy - y) > 0) Cam.verticalAngle = Cam.maxNangle;
		if (Cam.verticalAngle >= Cam.maxAngle && (prevy - y) < 0) Cam.verticalAngle = Cam.maxAngle;

		int w; int h;
		glfwGetWindowSize(window, &w, &h);

		prevx = (float)w / 2;
		prevy = (float)h / 2;

		glfwSetCursorPos(window, (double)w / 2, (double)h / 2);
	}