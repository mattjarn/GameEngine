#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "mat4.h"

class Renderer
{
public:
	// window
	GLFWwindow *window;
	// window settings
	//const unsigned int SCR_WIDTH = 1800, SCR_HEIGHT = 1200;
	//float deltaTime = 0.0f;	// Time between current frame and last frame
	//float lastFrame = 0.0f; // Time of last frame
	//float currentFrame = 0.0f;
	//Camera cam;

	/*unsigned int VAO[2];
	unsigned int VBO[2];*/
	//unsigned int VBO, VAO;

	Renderer();
	~Renderer();

	void StartUp();

	int shadows();

	void setupVertices();

	void Draw();

};

#endif // RENDERER_H