#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
//#include "Shader.h"
#include "mat4.h"
#include <glad/glad.h>  
#include <GLFW/glfw3.h>

class Renderer
{
public:
	// window
	GLFWwindow * window;
	// window settings
	//const unsigned int SCR_WIDTH = 1800, SCR_HEIGHT = 1200;

	Renderer();
	~Renderer();

	void StartUp(const char* vertexPath);

	int MultipleLights();

	int BulletPhysics();

	int shadows();

};

#endif // RENDERER_H