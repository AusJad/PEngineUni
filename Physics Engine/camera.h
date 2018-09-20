#ifndef CAMERA_H
#define CAMERA_H

#include "RenderModuleStubb.h"
//#include <glm/glm.hpp>
#include "Maths.h"

//--------------------------------------------------------------------------------------

/**
* @class Camera
* @brief Class for creating updating and handling the camera object.
*
* @author Mat DeVene
* @version 01
* @date 02/04/2018
*/
class Camera
{
public:
	Camera::Camera( vec3 pos)
	{
		rotateSpeed = 6.0f;
		moveSpeed = 3.0f;
		speedDecay = 7.0f;
		fov = 50.0f;
		nearPlane = 0.01f;
		farPlane = 100.0f;
		aspectRatio = (4.0f / 3.0f);
		horizontalAngle = 180.0f;
		verticalAngle = 0.0f;
		maxlspeed = 100.0f;
		moveForward = false;
		moveBack = false;
		moveRight = false;
		moveLeft = false;
		lookDown = false;
		lookUp = false;
		maxAngle = 80.0f;
		maxNangle = -80.0f;
		birdseye = false;
		yoff = 30.0f;
	}

	void Camera::update(float time) {

		if (this->moveForward) {
			target += GetCamZ()* moveSpeed;
		}
		else
			if (this->moveBack) {
				target += -GetCamZ()* moveSpeed;
			}

		if (this->moveRight) {
			target += GetCamX()* moveSpeed;
		}
		else
			if (this->moveLeft) {
				target -= GetCamX()* moveSpeed;
			}

		if (this->lookDown) {
			target -= vec3(0, 1, 0)* moveSpeed;
		}
		else
			if (this->lookUp) {
				target += vec3(0, 1, 0)* moveSpeed;
			}

		pos += (target * (time * speedDecay));
		target -= (target * (time * speedDecay));
	}

	void Camera::stop() {
		moveForward = false;
		moveBack = false;
		moveRight = false;
		moveLeft = false;
		lookDown = false;
		lookUp = false;
		target = vec3();
	}

	void Camera::render() {
		RNDR->callLookAt(vec3(pos.x(), pos.y(), pos.z()),
			vec3(pos.x() + GetCamZ().x(), pos.y() + GetCamZ().y(), pos.z() + GetCamZ().z()),
			vec3(GetCamY().x(), GetCamY().y(), GetCamY().z()));
	}

	void Camera::SetFov(float fov) {
		assert(fov > 0.0f && fov < 180.0f);
		fov = fov;
	}

	void Camera::SetFrustrumNearFar(float nearPlane, float farPlane) {
		assert(nearPlane > 0.0f);
		assert(farPlane > nearPlane);
		nearPlane = nearPlane;
		farPlane = farPlane;
	}

	void Camera::Rotate(float upAngle, float rightAngle) {
		horizontalAngle += rightAngle;
		verticalAngle += upAngle;
		CorrectAngleBoundaries();
	}

	void Camera::LookAt(vec3 pos) {
		vec3 direction = Maths::normalize(pos - vec3(this->pos.x(), this->pos.y(), this->pos.z()));
		verticalAngle = Maths::radians(asinf(-direction.y()));
		horizontalAngle = -Maths::radians(atan2f(-direction.x(), -direction.z()));
		CorrectAngleBoundaries();
	}

	void Camera::SetPosition(const vec3& pos) {
		this->pos = pos;
	}

	void Camera::SetAspectRatio(float aspectRatio) {
		assert(aspectRatio > 0.0);
		this->aspectRatio = aspectRatio;
	}


	float Camera::GetFov() const {
		return fov;
	}

	float Camera::GetFrustrumNearPlane() const {
		return nearPlane;
	}

	float Camera::GetFrustrumFarPlane() const {
		return farPlane;
	}

	float Camera::GetAspectRatio() const {
		return aspectRatio;
	}

	mat4 Camera::GetDirection() const {
		mat4 direction;
		direction = Maths::rotate(direction, Maths::radians(verticalAngle), vec3(1, 0, 0));
		direction = Maths::rotate(direction, Maths::radians(horizontalAngle), vec3(0, 1, 0));
		return direction;
	}

	vec3 Camera::GetCamX() const {
		vec4 right = Maths::inverse(GetDirection()) * vec4(1, 0, 0, 1);
		return vec3(right);
	}

	vec3 Camera::GetCamY() const {
		vec4 up = Maths::inverse(GetDirection()) * vec4(0, 1, 0, 1);
		return vec3(up);
	}

	vec3 Camera::GetCamZ() const {
		vec4 camZ = Maths::inverse(GetDirection()) * vec4(0, 0, -1, 1);
		return vec3(camZ);
	}

	mat4 Camera::GetTransMatrix() const {
		return GetProjectionMatrix() * GetViewMatrix();
	}

	mat4 Camera::GetProjectionMatrix() const {
		return Maths::perspective(Maths::radians(fov), aspectRatio, nearPlane, farPlane);
	}

	mat4 Camera::GetViewMatrix() const {
		return GetDirection() * Maths::translate(mat4(), vec3(pos.x() * -1, pos.y() * -1, pos.z() * -1));
	}

	void Camera::CorrectAngleBoundaries() {
		horizontalAngle = fmodf(horizontalAngle, 360.0f);
		//fmodf can return negative values, but this will make them all positive
		if (horizontalAngle < 0.0f)
			horizontalAngle += 360.0f;

		if (verticalAngle > maxAngle)
			verticalAngle = maxAngle;
		else if (verticalAngle < maxNangle)
			verticalAngle = maxNangle;
	}

	vec3 Camera::getCenterOffset() {
		return vec3(0, yoff, 0);
	}

//private:
	vec3 pos;
	vec3 target;
	/// Move speed of camera.
	float moveSpeed;
	/// Rotation speed of camera.
	float rotateSpeed;
	/// Move speed decay rate.
	float speedDecay;
	/// If moving foward.
	bool moveForward;
	/// If moving backwards.
	bool moveBack;
	/// If moving right.
	bool moveRight;
	/// If moving left.
	bool moveLeft;
	/// If looking down.
	bool lookDown;
	/// If looking up.
	bool lookUp;
	/// Max speed of the camera.
	float maxlspeed;
	/// Field of View.
	float fov;
	/// Aspect ratio.
	float aspectRatio;
	/// Near plane.
	float nearPlane;
	/// Far plane.
	float farPlane;
	/// Horizontal Angle.
	float horizontalAngle;
	/// Verticle Angle.
	float verticalAngle;
	/// Max angle.
	float maxAngle;
	/// Max angle of the n angle.
	float maxNangle;
	/// If the camera is birds eye view or not.
	bool birdseye;
	/// The y offset data.
	float yoff;
	

};

#endif