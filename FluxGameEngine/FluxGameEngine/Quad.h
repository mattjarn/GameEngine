#ifndef QUAD_H
#define QUAD_H

#include "vec4.h"
#include "mat4.h"

# define toRadians  (PI/180.0f)

struct Quad
{
	vec4 position = vec4(0.0f, 0.0f, 0.0f);
	unsigned int VAO, VBO;

	mat4 rotation;

	float vertices[30] = {
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
		0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
	};

	Quad() {

	};

	void SetPosition(float x, float y, float z) {
		this->position.elts[0] = x;
		this->position.elts[1] = y;
		this->position.elts[2] = z;
	};

	void SetRotation(float x, float y, float z) {
		this->rotation = mat4::createRotationMat(x, y, z);
	};

	//void Draw(mat4 view, Texture t, int width, int height) {

	//	Shader ourShader("shader.vs", "shader.fs");

	//	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	//	ourShader.use();
	//	ourShader.setInt("texture1", 0);
	//	ourShader.setInt("texture2", 1);

	//	// bind textures on corresponding texture units
	//	glActiveTexture(GL_TEXTURE1);
	//	t.Bind();
	//	float x = (float)glfwGetTime();

	//	glGenVertexArrays(1, &VAO);
	//	glGenBuffers(1, &VBO);

	//	glBindVertexArray(VAO);

	//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);

	//	// position attribute
	//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//	glEnableVertexAttribArray(0);
	//	// texture attribute
	//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//	glEnableVertexAttribArray(1);

	//	mat4 projection = mat4::perspective((45.0f * toRadians), (float)width / (float)height, 0.1f, 1000.0f);
	//	ourShader.setMat4("projection", projection);

	//	mat4 model = mat4::createTranslationMat(this->position);
	//	mat4 modelView = rotation * model * view;
	//	ourShader.setMat4("modelView", modelView);
	//	glBindVertexArray(VAO);
	//	glDrawArrays(GL_TRIANGLES, 0, 6);

	//};

};

#endif //QUAD_H