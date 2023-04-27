#pragma once
#include "stdafx.h"

class Mesh
{
public:
	template <typename T>
	Mesh(const vector<Vec3<T>>& vertices, const vector<int>& indices)
		:vertexCount(indices.size())
	{
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		glGenBuffers(1, &this->EBO);

		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vec3<T>), &vertices[0], GL_STATIC_DRAW);

		//cout << "vertexCount: " << this->vertexCount * sizeof(int) << endl;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->vertexCount * sizeof(int), &indices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, Vec3<T>::size(), GL_FLOAT, GL_FALSE, sizeof(Vec3<T>), (void*)0);
		glEnableVertexAttribArray(0);


		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	~Mesh()
	{
		glDeleteBuffers(1, &this->VBO);
		glDeleteBuffers(1, &this->EBO);
		glDeleteVertexArrays(1, &this->VAO);
	}

	void draw()
	{
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, this->vertexCount, GL_UNSIGNED_INT, 0);
	}
private:
	unsigned int VBO, VAO, EBO;
	unsigned int vertexCount;
};
