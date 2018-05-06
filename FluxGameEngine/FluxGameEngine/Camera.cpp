//#include "Camera.h"
//
//# define pi 3.14159265358979323846264338327950288419716939937510582
//# define toRadians  (pi/180.0f)
//
//// Constructor with vectors
//Camera::Camera(vec4 position, vec4 up, GLfloat yaw, GLfloat pitch) {
//	this->Position = position;
//	this->Up = up;
//	this->Yaw = yaw;
//	this->Pitch = pitch;
//	this->Zoom = ZOOM;
//}
//
//// Constructor with scalar values
//Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) {
//
//}
//
//mat4 Camera::GetViewMatrix() {
//	return this->ViewMat;
//}
//mat4 Camera::GetProjMatrix() {
//	return this->ProjMat;
//}
//
//void Camera::SetSpeed(float val) {
//	this->MovementSpeed = val;
//}
//
//void Camera::SetPosition(float x, float y, float z) {
//	this->Position.elts[0] = x;
//	this->Position.elts[1] = y;
//	this->Position.elts[2] = z;
//}
//
//// Processes input received from any keyboard-like input system. 
////Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
//void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime) {
//
//	GLfloat velocity = deltaTime * MovementSpeed;
//
//	switch (direction) {
//	case FORWARD:
//		this->Position = this->Position + (this->Fwd * velocity);
//		break;
//	case BACKWARD:
//		this->Position = this->Position + (this->Fwd * -velocity);
//		break;
//	case RIGHT:
//		this->Position = this->Position + (this->Right * velocity);
//		break;
//	case LEFT:
//		this->Position = this->Position + (this->Right * -velocity);
//		break;
//	}
//}
//
//// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
//void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch) {
//
//	//xoffset *= this->MouseSensitivity;
//	//yoffset *= this->MouseSensitivity;
//
//	//this->Yaw += xoffset;
//	//this->Pitch += yoffset;
//
//	//// Make sure that when pitch is out of bounds, screen doesn't get flipped
//	//if (constrainPitch)
//	//{
//	//	if (this->Pitch > 89.0f)
//	//		this->Pitch = 89.0f;
//	//	if (this->Pitch < -89.0f)
//	//		this->Pitch = -89.0f;
//	//}
//	//vec4 axis = vec4(0, 1, 0);
//	//quaternion q = quaternion(axis, -xoffset);
//	//this->Fwd = (q * this->Fwd);
//	//axis = vec4(1, 0, 0);
//	//q = quaternion(axis, yoffset);
//	//this->Fwd = (q * this->Fwd);
//
//	xoffset *= MouseSensitivity;
//	yoffset *= MouseSensitivity;
//
//	Yaw += xoffset;
//	Pitch += yoffset;
//
//	// Make sure that when pitch is out of bounds, screen doesn't get flipped
//	if (constrainPitch)
//	{
//		if (Pitch > 89.0f)
//			Pitch = 89.0f;
//		if (Pitch < -89.0f)
//			Pitch = -89.0f;
//	}
//
//	// Update Front, Right and Up Vectors using the updated Euler angles
//	updateCameraVectors();
//}
//
//// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
//void Camera::ProcessMouseScroll(GLfloat yoffset) {
//	if (Zoom >= 1.0f && Zoom <= 45.0f)
//		Zoom -= yoffset;
//	if (Zoom <= 1.0f)
//		Zoom = 1.0f;
//	if (Zoom >= 45.0f)
//		Zoom = 45.0f;
//}
//
////void Camera::updateCameraVectors() {
////	
////	mat4 look;
////	vec4 Y;
////
////	this->Fwd = this->Position - (this->Position + this->Fwd);
////	vec4::normalize(this->Fwd);
////	Y = this->Up;
////	Right = vec4::cross(Y, this->Fwd);
////
////	Y = vec4::cross(this->Fwd, this->Right);
////
////	vec4::normalize(this->Right);
////	vec4::normalize(Y);
////
////	look.m_elements[0][0] = this->Right.elts[0];
////	look.m_elements[1][0] = this->Right.elts[1];
////	look.m_elements[2][0] = this->Right.elts[2];
////	look.m_elements[3][0] = -vec4::dot(this->Right, this->Position);
////	look.m_elements[0][1] = Y.elts[0];
////	look.m_elements[1][1] = Y.elts[1];
////	look.m_elements[2][1] = Y.elts[2];
////	look.m_elements[3][1] = -vec4::dot(Y, this->Position);
////	look.m_elements[0][2] = this->Fwd.elts[0];
////	look.m_elements[1][2] = this->Fwd.elts[1];
////	look.m_elements[2][2] = this->Fwd.elts[2];
////	look.m_elements[3][2] = -vec4::dot(this->Fwd, this->Position);
////	look.m_elements[0][3] = 0;
////	look.m_elements[1][3] = 0;
////	look.m_elements[2][3] = 0;
////	look.m_elements[3][3] = 1.0f;
////
////	ViewMat = look;
////
////}
//
//// Calculates the front vector from the Camera's (updated) Euler Angles
//void Camera::updateCameraVectors()
//{
//	// Calculate the new Front vector
//	vec4 front;
//	front.elts[0] = cos((Yaw * toRadians)) * cos((Pitch * toRadians));
//	front.elts[1] = sin((Pitch * toRadians));
//	front.elts[2] = sin((Yaw * toRadians)) * cos((Pitch * toRadians));
//	Fwd = vec4::normalize(front);
//	// Also re-calculate the Right and Up vector
//	Right = vec4::normalize(vec4::cross(Fwd, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
//	Up = vec4::normalize(vec4::cross(Right, Fwd));
//}