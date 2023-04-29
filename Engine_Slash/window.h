#pragma once
#include "stdafx.h"

static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Window
{
	GLFWwindow* window;

public:
	Window(const int width, const int height, const char* title)
	{
		if (!glfwInit())
			abort();

		glfwSetErrorCallback(error_callback);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		this->window = glfwCreateWindow(480, 360, "Title", NULL, NULL);

		if (!this->window) {
			glfwTerminate();
			exit(EXIT_FAILURE);
			abort();
		}
		glfwMakeContextCurrent(this->window);
		glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		glfwSetKeyCallback(this->window, key_callback);


		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			abort();
		}
		glfwSwapInterval(1);
	}
	
	~Window()
	{
		glfwDestroyWindow(this->window);
		glfwTerminate();
	}

	bool shouldClose() const
	{
		glfwSwapBuffers(this->window);
		glfwPollEvents();
		glClearColor(.2f, .3f, .1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		return glfwWindowShouldClose(this->window);
	}

	vec2 getPos() const
	{
		int x, y;
		glfwGetWindowPos(this->window, &x, &y);
		return vec2({ (float)x, (float)y });
	}

	vec2 getPixel() const
	{
		int width, height;
		glfwGetWindowSize(this->window, &width, &height);
		return vec2({ (float)width, (float)height });
	}

	vec2 getSize() const
	{
		int width, height;
		glfwGetFramebufferSize(this->window, &width, &height);
		return vec2({ 1.f, (float)height / width });
	}

	vec2 getMouse() const
	{
		double x, y;
		glfwGetCursorPos(this->window, &x, &y);
		int width, height;
		glfwGetWindowSize(this->window, &width, &height);
		x /= width;
		y /= height;
		x *= 2.f;
		y *= 2.f;
		x -= 1.f;
		y = 1.f - y;
		return vec2({ (float)x, (float)y });
	}
};

static void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}