#pragma once
#include "stdafx.h"

class Shader
{
	unsigned int id;
public:
	Shader(const char* filepath)
		:id(glCreateProgram())
	{
		ifstream file(filepath);
		if (file.is_open())
		{
			string line;
			string content;
			GLenum shader_type = 0;
			vector<unsigned int> shaderIDs;

			while (getline(file, line))
			{
				if (line[0] == '%')
				{
					line = trim(line.substr(1));
					if (line.rfind("vertex") == 0)
						compileShader(shader_type, content, shaderIDs, GL_VERTEX_SHADER);
					else if (line.rfind("fragment") == 0)
						compileShader(shader_type, content, shaderIDs, GL_FRAGMENT_SHADER);
				}
				else {
					content += line + '\n';
				}
			}

			compileShader(shader_type, content, shaderIDs, 0);
			glLinkProgram(id);

			int success;
			char infoLog[512];
			glGetProgramiv(id, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(id, 512, NULL, infoLog);
				cout << "ERROR:SHADER:PROGRAM_FAILED!\n" << infoLog << endl;
			}
			for (size_t i = 0; i < shaderIDs.size(); i++)
				glDeleteShader(shaderIDs[i]);
		}
		else
		{
			cout << "ERROR:SHADER:FILE_NOT_SUCCESFULLY_READ!" << endl;
		}
	}

	~Shader()
	{
		glDeleteProgram(id);
	}

	void use()
	{
		glUseProgram(id);
	}

	void setBool(const string& name, bool value) const
	{
		glUseProgram(this->id);
		glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int)value);
	}

	void setInt(const string& name, int value) const
	{
		glUseProgram(this->id);
		glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
	}

	void setFloat(const string& name, float value) const
	{
		glUseProgram(this->id);
		glUniform1f(glGetUniformLocation(this->id, name.c_str()), value);
	}

	void setVec2(const string& name, const vec2& value) const
	{
		glUseProgram(this->id);
		glUniform2fv(glGetUniformLocation(this->id, name.c_str()), 1, &value.x);
	}

	void setVec3(const string& name, const vec3& value) const
	{
		glUseProgram(this->id);
		glUniform3fv(glGetUniformLocation(this->id, name.c_str()), 1, &value.x);
	}

private:
	void compileShader(GLenum& shader_type, string& content, vector<unsigned int>& shaderIDs, const GLenum& next_shader_type)
	{
		if (shader_type)
		{
			unsigned int shader;
			shader = glCreateShader(shader_type);
			const char* resource = content.c_str();
			glShaderSource(shader, 1, &resource, NULL);
			glCompileShader(shader);

			int success;
			char infoLog[512];
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				cout << "ERROR:SHADER:COMPILATION_FAILED!\n" << infoLog << endl;
			}

			glAttachShader(id, shader);
			shaderIDs.push_back(shader);
		}

		content = "";
		shader_type = next_shader_type;
	}
};
