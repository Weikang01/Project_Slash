#pragma once
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <assert.h>
#define STB_IMAGE_IMPLEMENTATION

using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;
using std::string;
using std::getline;
using std::array;
using std::vector;

std::string trim(const std::string& s);


template<typename T, size_t N>
struct Vector
{
	T vars[N];

    Vector(std::initializer_list<T> items)
	{
		std::copy(items.begin(), items.end(), vars);
	}

    Vector(T value)
    {
		std::fill_n(vars, N, value);
	}

    Vector()
        :vars{ 0 }
    {}

	static int size()
    {
        return N;
	}

	static int T_size()
	{
		return sizeof(T);
	}

	friend ostream& operator<<(ostream& os, const Vector<T, N>& vec)
	{
		os << "vec" << N << "(" << vars[0];
		for (size_t i = 1; i < N; i++)
		{
			os << ", " << vars[i];
		}

		os << ")";
		return os;
	}
};


using vec2 = Vector<float, 2>;
using ivec2 = Vector<int, 2>;
using uvec2 = Vector<unsigned int, 2>;

using vec3 = Vector<float, 3>;
using ivec3 = Vector<int, 3>;
using uvec3 = Vector<unsigned int, 3>;

using vec4 = Vector<float, 4>;
using ivec4 = Vector<int, 4>;
using uvec4 = Vector<unsigned int, 4>;


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

	template<size_t N, typename ... Args>
	Vertex(Vector<T, N> elements, Args&&... args)
	{
		initialize(elements, args...);
		assert(this->elements.size() == Vertex<T>::indices.back());
	}

	Vertex() {}

	static void setIndices(vector<int> indices)
	{
		Vertex<T>::indices = indices;
	}

	template<size_t N, typename ... Args>
	static void setIndices(Vector<T, N> elements, Args&&... args)
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

	template<size_t N, typename ... Args>
	void initialize(Vector<T, N> elements, Args&&... args)
	{
		this->elements.insert(this->elements.end(), elements.vars, elements.vars + N);
		initialize(args...);
	}

	static void _setIndices() {}

	template<size_t N, typename ... Args>
	static void _setIndices(Vector<T, N> elements, Args&&... args)
	{
		Vertex<T>::indices.push_back(Vertex<T>::indices.back() + N);
		Vertex<T>::_setIndices(args...);
	}
};

template<typename T>
vector<int> Vertex<T>::indices = { 0 };

using vertex = Vertex<float>;