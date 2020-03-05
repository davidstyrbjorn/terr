#include"../include/window.h"

#include<GLFW/glfw3.h>

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
		// @ WE PROBABLY WANT TO DO SOMETHING DEBUG LOG RELAYED HERE
		return;
	}

	// Make the glfw window the current context so that OpenGL know's where we are renderig our shit
	glfwMakeContextCurrent(glfw_window);
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

void terr::Window::Clear() {
	// Clear the color and depth buffer 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4f, 0.8f, 0.4f, 1.0f);
}

void terr::Window::Display() {
	// Swap so that this cycles render buffer is the one showing
	glfwSwapBuffers(glfw_window);

	// Poll events preparing for the next cycle
	glfwPollEvents();
}
