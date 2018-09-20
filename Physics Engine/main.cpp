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

void physUpdate(phys::Rectangle & r1, phys::Rectangle & r2) {
	r1.update(ttime, vec3(0,0,0));
	r2.update(ttime, vec3(.5, 0, 0));

	if (OBBOBB(r1.getOBB(), r2.getOBB())) {
		CollisionManifold coll = FindCollisionFeatures(r1.getOBB(), r2.getOBB());
		if (coll.colliding) {
			for(unsigned i = 0; i < coll.contacts.size(); i++) std::cout << coll.contacts.at(i) << std::endl;

			std::cout << coll.depth <<std::endl;
		}
	}
	
}

void init() {
	rect.orientate(ZRotation3x3(-45));
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