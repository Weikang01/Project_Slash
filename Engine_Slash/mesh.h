#pragma once
#include "stdafx.h"

class Mesh
{
private:
	template<typename T>
	vector<T> getVertices(const vector<Vertex<T>>& vertices)
	{
		vector<T> result;
		for (size_t i = 0; i < vertices.size(); i++)
			result.insert(result.end(), vertices[i].elements.begin(), vertices[i].elements.end());
		return result;
	}

public:
	template <typename T>
	Mesh(const vector<Vertex<T>>& vertices, const vector<int>& indices)
		:vertexCount(indices.size())
	{
		vector<T> vertices_ = getVertices(vertices);

		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		glGenBuffers(1, &this->EBO);

		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(T), &vertices_[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->vertexCount * sizeof(int), &indices[0], GL_STATIC_DRAW);

		for (size_t i = 0; i < Vertex<T>::indices.size() - 1; i++)
		{
			glVertexAttribPointer(i, Vertex<T>::element_size(i), GL_FLOAT, GL_FALSE,
				Vertex<T>::size() * sizeof(T),
				(void*)(Vertex<T>::offset(i) * sizeof(T)));
			glEnableVertexAttribArray(i);
		}

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
