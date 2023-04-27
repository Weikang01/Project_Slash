#include "stdafx.h"
#include "window.h"
#include "shader.h"
#include "mesh.h"

vector<vec3> vertices = {
	vec3( 1.0f,  1.0f, 0.0f),  // top right
	vec3( 1.0f, -1.0f, 0.0f),  // bottom right
	vec3(-1.0f, -1.0f, 0.0f),  // bottom left
	vec3(-1.0f,  1.0f, 0.0f)   // top left
};

vector<int> indices = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};


int main() {

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

	return 0;
}
