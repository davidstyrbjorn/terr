#pragma once

struct GLFWwindow;
struct GLFWmonitor;

#include<string>
#include<vector>

#include"Input.h"

namespace terr {

	class Color;

	class Window {

	public:
		Window(int _width, int _height, std::string _title, bool _fullScreen); // Default constructor, constructs a window with given width and height
		~Window();

		bool IsOpen();
		void Clear(Color color);
		void Display();

		void PollEvent(Event& event);
		void FlushEvents();
		std::vector<Event>& GetEvents();

		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	public:
		int width, height;
		int windowed_width, windowed_height;
		GLFWwindow* glfw_window;
		GLFWmonitor* glfw_monitor;
		std::vector<Event> event_queu;

		static int KEYS[1028];
	};
	
}