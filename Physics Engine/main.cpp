// Physics Engine.cpp : Defines the entry point for the console application.
//

#include "RenderModuleStubb.h"
#include "camera.h"
#include "Particle.h"
#include "Rectangle.h"

//Basic engine setup
#if true

Camera Cam(vec3(-.5, 0, 0));

phys::Rectangle rect(vec3(20, 1, 1), 3, 2, 2);

phys::Rectangle rect2(vec3(-10, 1, 1), 2, 2, 2);

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

physvec3 magicEquation(physvec3 obj1LinearVelocity, physvec3 obj2LinearVelocity, physvec3 obj1AngularVelocity, physvec3 obj2AngularVelocity, float obj1Mass, float obj2Mass, physvec3 obj1R, physvec3 obj2R, physmat4 obj1InertiaTensor, physmat4 obj2InertiaTensor, physvec3 collisionVector)
{
	if ((1/obj1Mass) + (1/obj2Mass) == 0.0f) {
		return physvec3(0,0,0);
	}
	float bottomBit;
	physvec3 relativeLinearVelocity;
	relativeLinearVelocity.x = obj1LinearVelocity.x - obj2LinearVelocity.x;
	relativeLinearVelocity.y = obj1LinearVelocity.y - obj2LinearVelocity.y;
	relativeLinearVelocity.z = obj1LinearVelocity.z - obj2LinearVelocity.z;
	mat3 i1;
	mat3 i2;
	i1._11 = obj1InertiaTensor._11;
	i1._12 = obj1InertiaTensor._12;
	i1._13 = obj1InertiaTensor._13;

	i1._21 = obj1InertiaTensor._21;
	i1._22 = obj1InertiaTensor._22;
	i1._23 = obj1InertiaTensor._23;

	i1._31 = obj1InertiaTensor._31;
	i1._32 = obj1InertiaTensor._32;
	i1._33 = obj1InertiaTensor._33;


	i2._11 = obj2InertiaTensor._11;
	i2._12 = obj2InertiaTensor._12;
	i2._13 = obj2InertiaTensor._13;

	i2._21 = obj2InertiaTensor._21;
	i2._22 = obj2InertiaTensor._22;
	i2._23 = obj2InertiaTensor._23;

	i2._31 = obj2InertiaTensor._31;
	i2._32 = obj2InertiaTensor._32;
	i2._33 = obj2InertiaTensor._33;

	i1 = Inverse(i1);
	i2 = Inverse(i2);

	//inverse mass
	float inverseMasses = (1 / obj1Mass) + (1 / obj2Mass);
	bottomBit = Dot(Cross(obj1R, collisionVector), MultiplyVector(i1,Cross(obj1R, collisionVector))) + Dot(Cross(obj2R, collisionVector), MultiplyVector(i2, Cross(obj2R, collisionVector)));
	bottomBit += inverseMasses;
	float topBit = (-(1 + 0.5) * Dot(collisionVector, relativeLinearVelocity) + Dot(obj1AngularVelocity, Cross(obj1R, collisionVector)) - (Dot(obj2AngularVelocity, Cross(obj2R, collisionVector))));

	float magic = topBit /= bottomBit; 

	collisionVector.x *= magic;
	collisionVector.y *= magic;
	collisionVector.z *= magic;

	return (collisionVector);
}

void updateLinearVelocity(phys::Rectangle & r1, phys::Rectangle & r2, physvec3 help)
{

	r1.vel.x += (help.x / r1.mass);
	r1.vel.y += (help.y / r1.mass);
	r1.vel.z += (help.z / r1.mass);


	r2.vel.x -= (help.x / r2.mass);
	r2.vel.y -= (help.y / r2.mass);
	r2.vel.z -= (help.z / r2.mass);
}

void updateAngularVelocity(phys::Rectangle & r1, phys::Rectangle & r2, physvec3 help, physvec3 collPt)
{
	physvec3 normalVector = collPt - r1.getOBB().position;
	mat3 i1;
	mat3 i2;
	i1._11 = r1.intert_tensor._11;
	i1._12 = r1.intert_tensor._12;
	i1._13 = r1.intert_tensor._13;

	i1._21 = r1.intert_tensor._21;
	i1._22 = r1.intert_tensor._22;
	i1._23 = r1.intert_tensor._23;

	i1._31 = r1.intert_tensor._31;
	i1._32 = r1.intert_tensor._32;
	i1._33 = r1.intert_tensor._33;


	i2._11 = r2.intert_tensor._11;
	i2._12 = r2.intert_tensor._12;
	i2._13 = r2.intert_tensor._13;

	i2._21 = r2.intert_tensor._21;
	i2._22 = r2.intert_tensor._22;
	i2._23 = r2.intert_tensor._23;

	i2._31 = r2.intert_tensor._31;
	i2._32 = r2.intert_tensor._32;
	i2._33 = r2.intert_tensor._33;

	i1 = Inverse(i1);
	i2 = Inverse(i2);



	physvec3 r1stuff = MultiplyVector(i1, Cross(normalVector, collPt));
	r1.angularvel.x = r1.angularvel.x + help.x * r1stuff.x;
	r1.angularvel.y = r1.angularvel.y + help.y * r1stuff.y;
	r1.angularvel.z = r1.angularvel.z + help.z * r1stuff.z;

	physvec3 r2stuff = MultiplyVector(i2, Cross(normalVector, collPt));
	r2.angularvel.x = r2.angularvel.x - help.x * r2stuff.x;
	r2.angularvel.y = r2.angularvel.y - help.y * r2stuff.y;
	r2.angularvel.z = r2.angularvel.z - help.z * r2stuff.z;

}


void physUpdate(phys::Rectangle & r1, phys::Rectangle & r2) {
	r1.update(ttime);
	r2.update(ttime);


	physvec3 collpt;
	physvec3 obj1R;
	physvec3 obj2R;
	physvec3 momentumChange;

	if (OBBOBB(r1.getOBB(), r2.getOBB())) {
		CollisionManifold coll = FindCollisionFeatures(r1.getOBB(), r2.getOBB());
		if (coll.colliding) {
			if (coll.contacts.size() > 1)
			{
				for (int i = 0; i < coll.contacts.size() - 1; i++)
				{
					collpt += coll.contacts[i];
				}

				collpt /= coll.contacts.size();
			}
			else
			{
				collpt += coll.contacts[0];
				collpt /= coll.contacts.size();
			}

			obj1R = r1.getOBB().position + collpt;
			obj2R = r2.getOBB().position + collpt;

			momentumChange = magicEquation(r1.vel, r2.vel, r1.angularvel, r2.angularvel, r1.mass, r2.mass, obj1R, obj2R, r1.intert_tensor, r2.intert_tensor, collpt);
			updateAngularVelocity(r1, r2, momentumChange, collpt);
			updateLinearVelocity(r1, r2, momentumChange);
			
		
		}

	}
}



void init() {
		rect.mass = 5;
		rect2.mass = 5;
		rect.COR = .5;
		rect2.COR = .5;

		rect2.vel = physvec3(15, 0, 0);
		rect.vel = physvec3(-15, 5, 0);

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