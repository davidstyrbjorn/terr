#pragma once

struct GLFWwindow;
struct GLFWmonitor;

#include<string>

namespace terr {

	class Window {

	public:
		Window(int _width, int _height, std::string _title, bool _fullScreen); // Default constructor, constructs a window with given width and height
		~Window();

		bool IsOpen();
		void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f);
		void Display();

		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	public:
		int width, height;
		int windowed_width, windowed_height;
		GLFWwindow* glfw_window;
		GLFWmonitor* glfw_monitor;
	};
	
}