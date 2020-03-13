#include"../include/core/window.h"

#include<GLFW/glfw3.h>
#include"../include/core/debug_log.h"

terr::Window::Window(int _width, int _height, std::string _title,
	bool _fullScreen) : width(_width), height(_height)
{
	// Init GLFW
	if (!glfwInit()) {
		terr::DebugLog::Log<terr::Window>("Failed to initalize GLFW", DebugLog::Type::ERROR);
		return;
	}

	// Get the monitor reference
	glfw_monitor = glfwGetPrimaryMonitor();

	const GLFWvidmode* mode = glfwGetVideoMode(glfw_monitor);

	// Notify glfw of some monitor properties
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	// Tell GLFW to create our window
	if (_fullScreen) {
		windowed_width = 800; windowed_height = 600; // Default when fullscreen from the start
		glfw_window = glfwCreateWindow(mode->width, mode->height, _title.c_str(), glfw_monitor, NULL);
	}
	else {
		windowed_width = _width;
		windowed_height = _height;
		glfw_window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
	}

	if (!glfw_window) {
		glfwTerminate();
		terr::DebugLog::Log<terr::Window>("Failed to create GLFW window", DebugLog::Type::ERROR);
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
