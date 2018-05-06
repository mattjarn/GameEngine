#ifndef CAMERA_H
#define CAMERA_H

#include "vec4.h"
#include "mat4.h"

#include <vector>

# define m_pi 3.14159265358979323846264338327950
# define toRadians  (m_pi/180.0f)

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	// Camera Attributes
	vec4 Position;
	vec4 Front;
	vec4 Up;
	vec4 Right;
	vec4 WorldUp;
	// Euler Angles
	float Yaw;
	float Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	// Constructor with vectors
	Camera(vec4 position = vec4(0.0f, 0.0f, 0.0f), vec4 up = vec4(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(vec4(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	// Constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(vec4(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = vec4(posX, posY, posZ);
		WorldUp = vec4(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	mat4 GetViewMatrix()
	{
		return mat4::lookAt(Position, Position + Front, Up);
	}

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			Position = Position + (Front * velocity);
		if (direction == BACKWARD)
			Position = Position + (Front * -velocity);
		if (direction == LEFT)
			Position = Position + (Right * -velocity);
		if (direction == RIGHT)
			Position = Position + (Right * velocity);
	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// Update Front, Right and Up Vectors using the updated Euler angles
		updateCameraVectors();
	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovementOther(float xoffset, float yoffset)
	{
		xoffset *= MouseSensitivity * 0.05;
		yoffset *= MouseSensitivity * 0.05;

		Position = Position + (Right * -xoffset);
		Position = Position + (Up * -yoffset);


		// Update Front, Right and Up Vectors using the updated Euler angles
		updateCameraVectors();
	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset)
	{
		if (Zoom >= 1.0f && Zoom <= 45.0f)
			Zoom -= yoffset;
		if (Zoom <= 1.0f)
			Zoom = 1.0f;
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
	}

private:
	// Calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors()
	{
		// Calculate the new Front vector
		vec4 front;
		front.elts[0] = cos(Yaw * toRadians) * cos(Pitch * toRadians);
		front.elts[1] = sin(Pitch * toRadians);
		front.elts[2] = sin(Yaw * toRadians) * cos(Pitch * toRadians);
		Front = vec4::normalize(front);
		// Also re-calculate the Right and Up vector
		Right = vec4::normalize(vec4::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = vec4::normalize(vec4::cross(Right, Front));
	}
};
#endif