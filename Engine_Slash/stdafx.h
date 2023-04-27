#pragma once
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::getline;
using std::vector;

std::string trim(const std::string& s);

template<typename T>
struct Vec2
{
	T x, y;
	Vec2(T x, T y)
		:x(x), y(y)
	{}
	Vec2(T value)
		:x(value), y(value)
	{}
	Vec2()
		:x(0), y(0)
	{}
	static int size()
	{
		return 2;
	}
};

template<typename T>
struct Vec3
{
    T x, y, z;

    Vec3(T x, T y, T z)
		:x(x), y(y), z(z)
	{}

    Vec3(T value)
        :x(value), y(value), z(value)
    {}

    Vec3()
        :x(0), y(0), z(0)
    {}

    static int size()
    {
        return 3;
	}
};

template<typename T>
struct Vec4
{
	T x, y, z, w;
	Vec4(T x, T y, T z, T w)
		:x(x), y(y), z(z), w(w)
	{}
	Vec4(T value)
		:x(value), y(value), z(value), w(value)
	{}
	Vec4()
		:x(0), y(0), z(0), w(0)
	{}
	static int size()
	{
		return 4;
	}
};

using vec3 = Vec3<float>;
using ivec3 = Vec3<int>;
using uvec3 = Vec3<unsigned int>;

using vec2 = Vec2<float>;
using ivec2 = Vec2<int>;
using uvec2 = Vec2<unsigned int>;

using vec4 = Vec4<float>;
using ivec4 = Vec4<int>;
using uvec4 = Vec4<unsigned int>;