#include "vec4.h"
#include "mat4.h"
#include "quaternion.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// A camera class that processes input and calculates the corresponding 
// View Matrices and Important Vectors
class Camera
{
public:
	// Camera Attributes
	vec4 Position;
	vec4 Fwd = vec4(0.0f, 0.0f, -1.0f);
	vec4 Up;
	vec4 Right;
	vec4 WorldUp = vec4(0.0f, 1.0f, 0.0f);

	mat4 ViewMat;
	mat4 ProjMat;

	// Euler Angles
	GLfloat Yaw;
	GLfloat Pitch;
	// Camera options
	GLfloat MovementSpeed = SPEED;
	GLfloat MouseSensitivity = SENSITIVITY;
	GLfloat Zoom = 45.0f;

	// Constructor with vectors
	Camera(vec4 position = vec4(0.0f, 0.0f, 0.0f), vec4 up = vec4(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);

	// Constructor with scalar values
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

	mat4 GetViewMatrix();
	mat4 GetProjMatrix();

	void SetSpeed(float val);

	void SetPosition(float x, float y, float z);

	// Processes input received from any keyboard-like input system. 
	//Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(GLfloat yoffset);

	// Calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors();
};