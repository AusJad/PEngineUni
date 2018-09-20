// Physics Engine.cpp : Defines the entry point for the console application.
//

#include "RenderModuleStubb.h"
#include "camera.h"
#include "Particle.h"
#include "Rectangle.h"

//Basic engine setup
#if true

Camera Cam(vec3(-.5,0,0));

phys::Rectangle rect(vec3(9, 1, 1), 3, 2, 2);

phys::Rectangle rect2(vec3(3, 1, 1), 2, 2, 2);

double prevx = -1, prevy = -1;

float ttime = 0;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void mouseCallback(GLFWwindow* window, double x, double y);

#endif

void linearImpulse(phys::Rectangle & ob1, phys::Rectangle & ob2, CollisionManifold& m)
{
	float total_inv_mass = ob1.getInvMass() + ob2.getInvMass();

	if (total_inv_mass == 0)
	{
		return;
	}

	physvec3 relativeVelo = ob2.vel - ob1.vel;
	physvec3 relativeNormal = m.normal;
	Normalize(relativeNormal);

	if (Dot(relativeVelo, relativeNormal) > 0) // Objects are already moving away from each other
	{
		return;
	}

	float minCOR = fminf(ob1.COR, ob2.COR);
	float magnitude = 1 / total_inv_mass;

	if (m.contacts.size() > 0.0f && magnitude != 0.0f) // If there is a collision and it has a magnitude
		magnitude /= (float)m.contacts.size();

	physvec3 impulse = relativeNormal * magnitude;
	ob1.vel -= impulse * ob1.getInvMass();
	ob2.vel += impulse * ob2.getInvMass();
}

void physUpdate(phys::Rectangle & r1, phys::Rectangle & r2) {
	r1.update(ttime);
	r2.update(ttime);

	if (OBBOBB(r1.getOBB(), r2.getOBB())) {
		CollisionManifold coll = FindCollisionFeatures(r1.getOBB(), r2.getOBB());
		if (coll.colliding) {
			linearImpulse(r1, r2, coll);
			for(unsigned i = 0; i < coll.contacts.size(); i++) std::cout << coll.contacts.at(i) << std::endl;

			std::cout << coll.depth <<std::endl;
		}
	}
	
}

void init() {
	rect.orientate(ZRotation3x3(-45));
	rect.mass = 1;
	rect2.mass = 1;
	rect.COR = 0.5;
	rect2.COR = 0.5;

	rect2.vel = physvec3(15, 0, 0);
	rect.vel = physvec3(-15, 0, 0);
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