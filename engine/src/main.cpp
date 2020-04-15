#include"../include/core/shader.h"
#include"../include/core/engine.h"

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

class App : terr::TerrEngine {
public:
	App() : terr::TerrEngine(), shader("vertex.txt", "fragment.txt") {
		Start();
	}

	void OnUserStart() override {
		const float S = 25.0f;
		const int GRID_SQUARES = 32;

		float freq = 0;

		std::vector<vec3> points;
		for (int z = 0; z < GRID_SQUARES; z++) {
			for (int x = 0; x < GRID_SQUARES; x++) {
				freq+=0.1f;
				float y = S * sin(freq);
				points.push_back({ S * (float)x, y, S * (float)z });
			}
		}

		int squares_per_side = GRID_SQUARES - 1;
		int no_squares = squares_per_side * squares_per_side;
		index_count = no_squares * 6;

		unsigned int* indices = new unsigned int[index_count];

		int counter = 0;

		int pointer = 0;
		for (int i = 0; i < index_count; i++) {

			int _temp = GRID_SQUARES + 1;

			indices[i] = pointer; i += 1;
			indices[i] = pointer + 1; i += 1;
			indices[i] = pointer + _temp; i += 1;
			indices[i] = pointer; i += 1;
			indices[i] = pointer + _temp; i += 1;
			indices[i] = pointer + (_temp-1);

			counter++;

			if (counter == GRID_SQUARES-1) {
				pointer += 2;
				counter = 0;
			}
			else {
				pointer += 1;
			}
		}

		std::vector<uint> x(indices, indices + index_count);

		// Order goes: TOP-LEFT -> TOP-RIGHT -> BOTTOM-RIGHT and then TOP-LEFT -> BOTTOM-RIGHT -> BOTTOM-LEFT
		unsigned int xxxindices[] = {
			0, 1, 5,
			0, 5, 4,
		
			1, 2, 6,
			1, 6, 5,
		
			2, 3, 7,
			2, 7, 6,
		
			4, 5, 9,
			4, 9, 8,

			5, 6, 10,
			5, 10, 9,

			6, 7, 11,
			6, 11, 10,

			8, 9, 13,
			8, 13, 12,

			9, 10, 14,
			9, 14, 13,

			10, 11, 15, 
			10, 15, 14
		};

		// Create VAO
		glGenBuffers(1, &vao);
		glBindVertexArray(vao);

		// IBO
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, x.size() * sizeof(uint), &x.front(), GL_STATIC_DRAW);

		// Create VBO
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(vec3), &points.front(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Projection
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.001f, 1000.0f);
		//glm::mat4 proj = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
		shader.Enable();
		shader.UniformMat4x4("projection", proj);

	}

	void OnUserUpdate(float dt) override {
		std::cout << dt << std::endl;
		i++;
		clearColor.r = sin(0.001f * i);
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

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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

	return 0;
}

