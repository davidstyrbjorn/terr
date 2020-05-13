 #include"../include/core/shader.h"
#include"../include/core/engine.h"
#include"../include/core/terrain.h"
#include"../include/core/camera.h"

#include<iostream>
#include <iomanip>
#include<sstream>
#include<math.h>
#include<vector>

#define GLEW_STATIC
#include<GL/glew.h>

#include<GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4, glm::ivec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include"../include/imgui/imgui.h"

#define PI 3.14159265359f
#define DEG2RAD(x) (x*180.0f)/PI

int t = 0;

typedef unsigned int uint;

struct vec3 {
	float x, y, z;
};

struct uvec3 {
	uint x, y, z;
};

class Terrain {
	// Points, renderar
	// Anv�nder PerlinNoise klassen
	// PerlinNoise.evaluate(x,y), z - noise value
	// int Max-height
};

class Noise {

};

class PerlinNoise {

};

class App : public terr::TerrEngine {
public:
	App() : terrain() {
		
	}

	void OnUserStart() override {
		camera.createCamera(0,0,0, window);
		shader.CreateShader("vertex.txt", "fragment.txt");

		terrain.ConstructTerrain(32, glm::ivec3(1,1,1), 0);

		// Projection
		glm::mat4 proj = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.001f, 2000.0f);

		shader.Enable();
		shader.UniformMat4x4("projection", proj);

		SetupImGuiStyle();
	}

	void OnUserUpdate(float dt) override {
		// Update camera
		//camera.Update(dt);
	}

	void OnUserRender() override {

		auto in_color = glm::vec3(sin(t*0.01), 1, 0);

		// Send shit to the shader
		shader.UniformVec3("scale", terrain.scale); // Temporary
		shader.UniformVec3("in_color", in_color); // Sending color to fragment shader
		shader.UniformMat4x4("view_matrix", camera.GetViewMatrix());


		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		terrain.RenderTerrain();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void OnUserEvent(terr::Event event) override {
		// Send event to camera
		//camera.Event(event);
	}

	void OnUserExit() override {
	
	}

	void SetupImGuiStyle() {
		ImGuiStyle& style = ImGui::GetStyle();

		// light style from Pac�me Danhiez (user itamago) https://github.com/ocornut/imgui/pull/511#issuecomment-175719267
		style.Alpha = 1.0f;
		style.FrameRounding = 3.0f;
		style.WindowRounding = 0.0f;

		style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.94f);
		style.Colors[ImGuiCol_Border] = ImVec4(1.00f, 1.00f, 1.00f, 0.39f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.10f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.6f, 0.00f, 0.00f, 0.94f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.8f, 0.00f, 0.00f, 0.94f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.9f, 0.0f, 0.0f, 0.94f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.24f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.24f, 0.00f, 0.00f, 0.51f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.24f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		style.Colors[ImGuiCol_ComboBg] = ImVec4(0.14f, 0.14f, 0.14f, 0.99f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.73f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.43f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.73f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.44f, 0.00f, 0.00f, 0.40f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.73f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.79f, 0.00f, 0.00f, 0.31f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.80f, 0.00f, 0.00f, 0.80f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.78f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_Column] = ImVec4(0.95f, 0.00f, 0.61f, 1.00f);
		style.Colors[ImGuiCol_ColumnHovered] = ImVec4(1.00f, 0.00f, 0.29f, 0.78f);
		style.Colors[ImGuiCol_ColumnActive] = ImVec4(1.00f, 0.00f, 1.00f, 1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.34f, 0.00f, 0.00f, 0.50f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.00f, 0.00f, 0.67f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.57f, 0.00f, 0.00f, 0.95f);
		style.Colors[ImGuiCol_CloseButton] = ImVec4(0.48f, 0.00f, 0.01f, 0.50f);
		style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.74f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.19f, 0.00f, 0.35f);
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	}

private:
	unsigned int vao = 0;
	unsigned int vbo = 0;
	unsigned int ibo = 0;
	terr::Shader shader;
	terr::Terrain terrain;
	terr::Camera camera;

<<<<<<< HEAD
=======
	glm::vec3 view_position;
	glm::vec3 model_position;
	float view_x_rot = 0.0f;
	float view_zoom = 1.0f;

	float t = 0;
>>>>>>> parent of 20c3f1a... Resting on the pillow of time
};

int main() {
	App app = App();
	app.CreateWindow(1800, 900);



	return 0;
}