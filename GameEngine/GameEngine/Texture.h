#pragma once

#include <string>
#include <glad/glad.h>
#include <iostream>


enum TextureType {
	Albedo = 0,
	Diffuse = 1,
	Specular = 2,
	Normal = 3,
	Emission = 4,
};

class Texture
{
public:
	Texture(std::string filename, int w, int h, TextureType type);
	~Texture();

	void Bind();

private:
	GLuint textureID;

	TextureType type;
};