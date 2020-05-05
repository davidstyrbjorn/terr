 #include"../include/core/shader.h"
#include"../include/core/engine.h"
#include"../include/core/terrain.h"

#include<iostream>
#include <iomanip>
#include<sstream>
#include<math.h>
#include<vector>

#define GLEW_STATIC
#include<GL/glew.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4, glm::ivec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include"../include/imgui/imgui.h"

#define PI 3.14159265359f
#define DEG2RAD(x) (x*180.0f)/PI

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
	App() : terrain(32, 10) {
		
	}

	void OnUserStart() override {
		
		shader.CreateShader("vertex.txt", "fragment.txt");

		terrain.ConstructTerrain();

		// Projection
		glm::mat4 proj = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.001f, 2000.0f);
		//glm::mat4 proj = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
		shader.Enable();
		shader.UniformMat4x4("projection", proj);


	}

	void OnUserUpdate(float dt) override {


	}

	void OnUserRender() override {

		ImGui::Begin("test");
		ImGui::SliderAngle("View Rotation X", &view_x_rot);
		ImGui::SliderFloat("View Zoom", &view_zoom, 1.0f, 10.0f);
		ImGui::DragFloat3("View Position", &view_position[0]);
		ImGui::DragFloat3("Model Position", &model_position[0]);
		ImGui::End();

		// Upload some shit to the shader
		auto trans_view_matrix = glm::rotate(glm::mat4(1.0f), view_x_rot, glm::vec3(1, 0, 0));
		auto rot_view_matrix = glm::translate(glm::mat4(1.0f), -view_position);
		auto scale_view_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(view_zoom, view_zoom, 1));

		model_matrix = glm::translate(glm::mat4(1.0f), model_position);

		view_matrix = scale_view_matrix * trans_view_matrix * rot_view_matrix;

		shader.UniformMat4x4("view", view_matrix);
		shader.UniformMat4x4("model", model_matrix);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		terrain.RenderTerrain();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void OnUserEvent(terr::Event event) override {

	}

	void OnUserExit() override {
	
	}

private:
	unsigned int vao = 0;
	unsigned int vbo = 0;
	unsigned int ibo = 0;
	terr::Shader shader;
	terr::Terrain terrain;

	glm::vec3 view_position;
	glm::mat4 view_matrix;
	glm::mat4 model_matrix;
	glm::vec3 model_position;
	float view_x_rot = 0.0f;
	float view_zoom = 1.0f;

	int index_count;
	int i = 0;
};

int main() {
	App app = App();
	app.CreateWindow(1200, 700);

	return 0;
}