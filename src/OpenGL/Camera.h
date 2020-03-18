#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	Camera(glm::vec3 startPosition)
	{
		position = startPosition;
		updateCameraVectors();
	}

	glm::mat4 getViewMatrix()
	{
		return glm::lookAt(position, position + front, up);
	}

	float getFOV()
	{
		return zoom;
	}

	glm::vec3 getCameraPosition()
	{
		return position;
	}

	void processKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = movementSpeed * deltaTime;
		glm::vec3 right = glm::normalize(glm::cross(front, up));

		if (direction == FORWARD)
			position += front * velocity;
		if (direction == BACKWARD)
			position -= front * velocity;
		if (direction == LEFT)
			position -= right * velocity;
		if (direction == RIGHT)
			position += right * velocity;
	}

	void processMouseMovement(float xoffset, float yoffset)
	{
		xoffset *= mouseSensitivity;
		yoffset *= mouseSensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		updateCameraVectors();
	}

	void processMouseScroll(float yoffset)
	{
		if (zoom >= 1.0f && zoom <= 45.0f)
			zoom -= yoffset;
		if (zoom <= 1.0f)
			zoom = 1.0f;
		if (zoom >= 45.0f)
			zoom = 45.0f;
	}

	void processMouseClick()
	{
		zoom = !zoomed ? 20.0f : 45.0f;
		zoomed = !zoomed;
	}

private:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);

	float yaw = -90.0f;
	float pitch = 0.0f;

	float movementSpeed = 2.5f;
	float mouseSensitivity = 0.1f;
	float zoom = 45.0f;
	bool zoomed = false;

	void updateCameraVectors()
	{
		glm::vec3 tempFront;
		tempFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		tempFront.y = sin(glm::radians(pitch));
		tempFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(tempFront);
	}
};
#endif