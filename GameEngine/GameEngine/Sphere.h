//#pragma once
//#ifndef SPHERE_H
//#define SPHERE_H
//
//#include "vec4.h"
//#include "mat4.h"
//#include <vector>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "Shader.h"
//#include "Texture.h"
//
//Sphere sphere(1, 12, 24);
//#define PI		3.14159265358979323846
//#define PI_2	1.57079632679489661923
//
//
//struct Sphere
//{
//protected:
//	std::vector<float> vertices;
//	std::vector<float> normals;
//	std::vector<float> texcoords;
//	std::vector<float> indices;
//
//public:
//
//	unsigned int VBO, VAO;
//
//	Sphere(float radius, unsigned int rings, unsigned int sectors)
//	{
//		float const R = 1. / (float)(rings - 1);
//		float const S = 1. / (float)(sectors - 1);
//		int r, s;
//
//		vertices.resize(rings * sectors * 3);
//		normals.resize(rings * sectors * 3);
//		texcoords.resize(rings * sectors * 2);
//		std::vector<float>::iterator v = vertices.begin();
//		std::vector<float>::iterator n = normals.begin();
//		std::vector<float>::iterator t = texcoords.begin();
//		for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
//			float const y = sin(-PI_2 + PI * r * R);
//			float const x = cos(2 * PI * s * S) * sin(PI * r * R);
//			float const z = sin(2 * PI * s * S) * sin(PI * r * R);
//
//			*t++ = s * S;
//			*t++ = r * R;
//
//			*v++ = x * radius;
//			*v++ = y * radius;
//			*v++ = z * radius;
//
//			*n++ = x;
//			*n++ = y;
//			*n++ = z;
//		}
//
//		indices.resize(rings * sectors * 4);
//		std::vector<float>::iterator i = indices.begin();
//		for (r = 0; r < rings - 1; r++) for (s = 0; s < sectors - 1; s++) {
//			*i++ = r * sectors + s;
//			*i++ = r * sectors + (s + 1);
//			*i++ = (r + 1) * sectors + (s + 1);
//			*i++ = (r + 1) * sectors + s;
//		}
//	}
//
//	void draw(Texture t)
//	{
//		//Shader ourShader("vert.shader", "frag.shader");
//
//		//// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
//		//ourShader.use();
//		//ourShader.setInt("texture1", 0);
//
//		//// bind textures on corresponding texture units
//		//glActiveTexture(GL_TEXTURE0);
//		//t.Bind();
//
//		//glGenVertexArrays(1, &VAO);
//		//glGenBuffers(1, &VBO);
//
//		//glBindVertexArray(VAO);
//
//		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		//glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);
//
//		//// position attribute
//		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//		//glEnableVertexAttribArray(0);
//		//// texture attribute
//		//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//		//glEnableVertexAttribArray(1);
//
//		//mat4 projection = mat4::perspective((45.0f * toRadians), (float)width / (float)height, 0.1f, 100.0f);
//		//ourShader.setMat4("projection", projection);
//
//		//mat4 model = mat4::createTranslationMat(5, 1, 0);
//		//mat4 modelView = model * cam.ViewMat;
//		//ourShader.setMat4("modelView", modelView);
//		//glBindVertexArray(VAO);
//		//glDrawArrays(GL_TRIANGLES, 0, 24);
//	}
//
//};
//
//
//#endif //SPHERE_H
