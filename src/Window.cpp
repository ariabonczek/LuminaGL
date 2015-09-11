#include "Window.hpp"
#include "Utility\Input.hpp"

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
	// Enable multisampling
	glfwWindowHint(GLFW_SAMPLES, MSAA_SAMPLES);
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	// Back-face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_MULTISAMPLE);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Input::Initialize(window);
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