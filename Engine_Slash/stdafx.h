#pragma once
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <ostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <array>
#include <vector>
#include <assert.h>


using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;
using std::string;
using std::getline;
using std::array;
using std::vector;

std::string trim(const std::string& s);

using glm::vec2;
using glm::vec3;
using glm::vec4;

template<typename T>
struct Vertex
{
	static vector<int> indices;
	vector<T> elements;

	Vertex(std::initializer_list<T> items)
	{
		std::copy(items.begin(), items.end(), elements.begin());
		assert(elements.size() == Vertex<T>::indices.back());
	}

	Vertex(vector<T> elements)
		:elements(elements)
	{
		assert(this->elements.size() == Vertex<T>::indices.back());
	}

	template<size_t N, glm::qualifier Q, typename ... Args>
	Vertex(glm::vec<N, T, Q> elements, Args&&... args)
	{
		initialize(elements, args...);
		assert(this->elements.size() == Vertex<T>::indices.back());
	}

	Vertex() {}

	static void setIndices(vector<int> indices)
	{
		Vertex<T>::indices = indices;
	}

	template<size_t N, glm::qualifier Q, typename ... Args>
	static void setIndices(glm::vec<N, T, Q> elements, Args&&... args)
	{
		Vertex<T>::indices.resize(0);
		Vertex<T>::indices.push_back(0);
		Vertex<T>::_setIndices(elements, args...);
	}

	static int size()
	{
		return Vertex<T>::indices.back();
	}

	static int element_size(size_t index)
	{
		return Vertex<T>::indices[index + 1] - Vertex<T>::indices[index];
	}

	static int offset(size_t index)
	{
		return Vertex<T>::indices[index];
	}

private:
	void initialize() {}

	template<size_t N, glm::qualifier Q, typename ... Args>
	void initialize(glm::vec<N, T, Q> elements, Args&&... args)
	{
		this->elements.insert(this->elements.end(), glm::value_ptr(elements), glm::value_ptr(elements) + N);
		initialize(args...);
	}

	static void _setIndices() {}

	template<size_t N, glm::qualifier Q, typename ... Args>
	static void _setIndices(glm::vec<N, T, Q> elements, Args&&... args)
	{
		Vertex<T>::indices.push_back(Vertex<T>::indices.back() + N);
		Vertex<T>::_setIndices(args...);
	}
};

template<typename T>
vector<int> Vertex<T>::indices = { 0 };

using vertex = Vertex<float>;

