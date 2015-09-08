#include "Window.hpp"

NS_BEGIN

Window::Window()
{

}

Window::~Window()
{

}

void Window::Initialize(uint width, uint height, std::string title)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Clear(float x, float y, float z)
{
	glClearColor(x, y, z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Shutdown()
{
	glfwDestroyWindow(window);
}

int Window::ShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::Display()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
	glFlush();
}

NS_END