#include"../include/core/window.h"

#include<GLFW/glfw3.h>
#include"../include/core/debug_log.h"
#include"../include/core/color.h"
#include"../include/core/Input.h"

#include"../include/imgui/imgui.h"
#include"../include/imgui/imgui_impl_glfw_gl3.h"

int terr::Window::KEYS[1028] = {};

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
	glfwSetKeyCallback(glfw_window, key_callback);
	glfwSetScrollCallback(glfw_window, scroll_callback);
	glfwSetCharCallback(glfw_window, character_callback);

	// Mainly so that we can get Window class in the callback functions!
	glfwSetWindowUserPointer(glfw_window, this);

	// Initalize DearImGui stuff
	ImGui_ImplGlfwGL3_Init(glfw_window, false);
}

terr::Window::~Window()
{
	ImGui_ImplGlfwGL3_Shutdown();
	glfwTerminate();
}

// Simple function to tell if the GLFW is still open
bool terr::Window::IsOpen()
{
	return !glfwWindowShouldClose(glfw_window);
}

void terr::Window::Clear(Color color) {

	// Tell ImGui we're onto a new frame
	ImGui_ImplGlfwGL3_NewFrame();

	// Clear the color and depth buffer 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(color.r, color.g, color.b, 1.0f);
}

void terr::Window::Display() {

	// Tell ImGui to render just before we swap buffers!
	ImGui::Render();

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

/* EVENT RELATED FUNCTIONS!!! */

void terr::Window::PollEvent(Event& event)
{
	event_queu.push_back(event);
}

void terr::Window::FlushEvents()
{
	event_queu.clear();
}

std::vector<terr::Event>& terr::Window::GetEvents()
{
	return event_queu;
}

/* INPUT RELATED FUNCTIONS!!! */

void terr::Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static terr::Window* terr_window = static_cast<terr::Window*>(glfwGetWindowUserPointer(window));
	if (action == GLFW_PRESS) {
		terr::Event _event;
		_event.eventType = EventType::KEY_PRESSED;
		_event.key = key;

		terr_window->PollEvent(_event);

		terr_window->KEYS[key] = 1;
	}
	else if (action == GLFW_RELEASE) {
		terr::Event _event;
		_event.eventType = EventType::KEY_RELEASED;
		_event.key = key;

		terr_window->PollEvent(_event);

		terr_window->KEYS[key] = 0;
	}

	// ImGui callbacks!
	ImGui_ImplGlfwGL3_KeyCallback(window, key, scancode, action, mods);
}

void terr::Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	static terr::Window* terr_window = static_cast<terr::Window*>(glfwGetWindowUserPointer(window));
	if (action == GLFW_PRESS) {
		terr::Event _event;
		_event.eventType = EventType::MOUSE_DOWN;
		_event.button = button;

		terr_window->PollEvent(_event);
	}
	else if (action == GLFW_RELEASE) {
		terr::Event _event;
		_event.eventType = EventType::MOUSE_UP;
		_event.button = button;

		terr_window->PollEvent(_event);
	}

	// ImGui callbacks!
	ImGui_ImplGlfwGL3_MouseButtonCallback(window, button, action, mods);
}

void terr::Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	// ImGui callbacks!
	ImGui_ImplGlfwGL3_ScrollCallback(window, xoffset, yoffset);
}

void terr::Window::character_callback(GLFWwindow* window, unsigned int codepoint)
{
	// ImGui callbacks!
	ImGui_ImplGlfwGL3_CharCallback(window, codepoint);
}
