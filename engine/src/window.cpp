#include"../include/core/window.h"

#include<GLFW/glfw3.h>
#include"../include/core/debug_log.h"

terr::Window::Window(float _width, float _height, std::string _title) : width(_width), height(_height)
{
	// Init GLFW
	if (!glfwInit()) {
		return;
	}

	// Tell GLFW to create our window
	glfw_window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr); 

	if (!glfw_window) {
		glfwTerminate();
		terr::DebugLog::Log<terr::Window>("Failed to initalize GLFW!");
		return;
	}

	// Make the glfw window the current context so that OpenGL know's where we are renderig our shit
	glfwMakeContextCurrent(glfw_window);

	// Set some glfw callback functions!
	glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);

	// Mainly so that we can get Window class in the callback functions!
	glfwSetWindowUserPointer(glfw_window, this);
}

terr::Window::~Window()
{
	glfwTerminate();
}

// Simple function to tell if the GLFW is still open
bool terr::Window::IsOpen()
{
	return !glfwWindowShouldClose(glfw_window);
}

void terr::Window::Clear(float r, float g, float b) {
	// Clear the color and depth buffer 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(r, g, b, 1.0f);
}

void terr::Window::Display() {
	// Swap so that this cycles render buffer is the one showing
	glfwSwapBuffers(glfw_window);

	// Poll events preparing for the next cycle
	glfwPollEvents();
}

void terr::Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	
	static terr::Window* terr_window = static_cast<terr::Window*>(glfwGetWindowUserPointer(window));
	
	terr_window->width = width;
	terr_window->height = height;
}
