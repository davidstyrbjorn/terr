#pragma once

struct GLFWwindow;

#include<string>

namespace terr {

	class Window {

	public:
		Window(const Window& other) = delete; // No window copying is supported
		Window(float _width, float _height, std::string _title); // Default constructor, constructs a window with given width and height
		~Window();

		bool IsOpen();
		void Clear();
		void Display();

	private:
		float width, height;
		GLFWwindow* glfw_window;
	};
	
}