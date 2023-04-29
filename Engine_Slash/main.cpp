#include "stdafx.h"
#include "window.h"
#include "shader.h"
#include "mesh.h"

int main() {

	vertex::setIndices(vec3(), vec3(), vec2());

	vector<vertex> vertices = {
		vertex(vec3({ 1.0f,  1.0f, 0.0f}), vec3({1.0f, 0.0f, 0.0f}), vec2{1.0f, 1.0f}),  // top right
		vertex(vec3({ 1.0f, -1.0f, 0.0f}), vec3({0.0f, 1.0f, 0.0f}), vec2{1.0f, 0.0f}),  // bottom right
		vertex(vec3({-1.0f, -1.0f, 0.0f}), vec3({0.0f, 0.0f, 1.0f}), vec2{0.0f, 0.0f}),  // bottom left
		vertex(vec3({-1.0f,  1.0f, 0.0f}), vec3({1.0f, 1.0f, 0.0f}), vec2{0.0f, 1.0f})   // top left
	};

	vector<int> indices = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	//vertex v1 = { vec3({0.5f,  0.5f, 0.0f}), vec3({1.0f, 0.0f, 0.0f}), vec2({1.0f, 1.0f})};

	Window window(480, 360, "Title");

	Shader shader("./shaders/basic.shader");

	Mesh mesh(vertices, indices);

	while (!window.shouldClose())
	{
		shader.use();
		shader.setFloat("uTime", glfwGetTime());
		shader.setVec2("uResolution", window.getSize());
		shader.setVec2("uMouse", window.getMouse());
		mesh.draw();
	}

	//return 0;
}
