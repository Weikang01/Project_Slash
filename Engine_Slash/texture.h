#pragma once
#include "stdafx.h"

class Texture2D
{
	friend class Shader;
	unsigned int id;
public:
	static int TextCoord(int index)
	{
		return GL_TEXTURE0 + index;
	}

	Texture2D(const string& path)
	{
		glGenTextures(1, &this->id);
		glBindTexture(GL_TEXTURE_2D, this->id);
		int width, height, nrChannels;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			GLenum format;
			if (nrChannels == 1)
				format = GL_RED;
			else if (nrChannels == 3)
				format = GL_RGB;
			else if (nrChannels == 4)
				format = GL_RGBA;
			else format = GL_RGB;

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, format == GL_RGBA ? GL_LINEAR : GL_NEAREST);
		}
		else
		{
			cout << "ERROR:TEXTURE:FAILED_TO_LOAD_TEXTURE!" << endl;
		}
		stbi_image_free(data);
	}
};