#include"../include/core/shader.h"
#include"../include/core/engine.h"
#include"../include/core/terrain.h"
#include"../include/core/camera.h"
#include"../include/core/skybox.h"

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

typedef unsigned int uint;

class App : public terr::TerrEngine {
public:
	App() : terrain() {

	}

	void OnUserStart() override {
		camera.createCamera(0, 0, 0, window);
		shader.CreateShader("vertex.txt", "fragment.txt");

		//skybox.CreateSkybox();
		terrain.ConstructTerrain(32, glm::ivec3(10, 50, 10), 322);

		// Projection matrix
		glm::mat4 proj = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.001f, 2000.0f);

		shader.Enable();
		shader.UniformMat4x4("projection", proj);

		clearColor = terr::Color(0, 0.5, 0.9);

		SetupImGuiStyle();
	}

	void OnUserUpdate(float dt) override {
		// Update camera
		camera.Update(dt);
		terrain.UpdateTerrain(dt);
	}

	void OnUserRender() override {

		shader.Enable();
		// Send shit to the shader
		shader.UniformVec3("scale", terrain.scale); // Temporary
		shader.UniformMat4x4("view", camera.GetViewMatrix()); // Send the camera matrix
		shader.UniformVec3("lightPos", lightPos);
		shader.UniformVec3("lightColor", lightColor);

		//Temporary colors
		glm::vec3 colors[] = {
		glm::vec3(242/256.0f, 211/256.0f, 153 / 256.0f),
		glm::vec3(89 / 256.0f,68 / 256.0f, 49 / 256.0f),
		glm::vec3(166 / 256.0f,87 / 256.0f, 41 / 256.0f),
		glm::vec3(192 / 256.0f,222 / 256.0f, 136 / 256.0f),
		glm::vec3(92 / 256.0f,163 / 256.0f, 111 / 256.0f),
		glm::vec3(38 / 256.0f,91 / 256.0f,64 / 256.0f),
		glm::vec3(15 / 256.0f,62 / 256.0f,57 / 256.0f),
		glm::vec3(13 / 256.0f,33 / 256.0f,39 / 256.0f)
		};
		int array_size = 8;// Behöver ändras beroende på storlek av array
							//Kan vi få in denna i uniformvec3Array?
		

		//Send colors to fragment
		
		shader.UniformVec3Array("colors",colors);
		shader.UniformFloat("size_of_array", array_size); //sizeof() returns byte size of vec3 array

		terrain.RenderTerrain();

		ImGui::Begin("Light");
		ImGui::DragFloat3("Pos", &lightPos[0]);
		ImGui::ColorEdit3("Light Color", &lightColor[0]);
		ImGui::End();

	}

	void OnUserEvent(terr::Event event) override {
		// Send event to camera
		camera.Event(event);
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
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
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
	terr::Shader shader;
	terr::Terrain terrain;
	terr::Camera camera;
	//terr::Skybox skybox;
	glm::vec3 pos;
	glm::vec3 lightPos;
	glm::vec3 lightColor;
};

int main() {
	App app = App();
	app.CreateWindow(1200, 800);

	return 0;
}