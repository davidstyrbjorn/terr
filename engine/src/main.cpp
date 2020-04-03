#include"../include/core/window.h"

#include"../include/core/debug_log.h"
#include"../include/core/config.h"
#include"../include/core/clock.h"
#include"../include/core/vec3.h"
#include"../include/core/color.h"
#include"../include/core/Input.h"
#include"../include/core/shader.h"

#include<iostream>
#include<sstream>
#include<math.h>

#define GLEW_STATIC
#include<GL/glew.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4, glm::ivec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#define PI 3.14159265359f
#define DEG2RAD(x) (x*180.0f)/PI

typedef unsigned int uint;

struct vec3 {
	float x, y, z;
};

int main() {

	// This goes through the config files and gets the data 
	terr::Config::ParseFromConfigFile();

	// Open the DebugLog file
	terr::DebugLog::OpenDebugLog();

	// Create window
	terr::Window window = terr::Window(800, 600, "Terr", false);

	// GLEW init
	if (glewInit() != GLEW_OK) {
		std::cout << "glew failed to init" << std::endl;
	}

	// DOING SOME STUFF WITH PEN AND PAPER BRB

	std::vector<vec3> points;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			points.push_back({ (float)x, (float)y, 0 });
		}
	}

	float vertices[] = {
		 0.0f,  0.0f, 0.0f,   // top left 
		 1.0f,  0.0f, 0.0f,  // top right 
		 1.0f,  1.0f, 0.0f,  // bottom right 
		 0.0f,  1.0f, 0.0f  // bottom left 
	};

	// Order goes: TOP-LEFT -> TOP-RIGHT -> BOTTOM-RIGHT and then TOP-LEFT -> BOTTOM-RIGHT -> BOTTOM-LEFT
	unsigned int indices[] = {  
		0, 1, 5,   
		0, 5, 4,

		1, 2, 6,
		1, 6, 5


	};

	// Create VAO
	unsigned int vao;
	glGenBuffers(1, &vao);
	glBindVertexArray(vao);

	// IBO
	uint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Create VBO
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(vec3), &points.front(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	terr::Shader shader("vertex.txt", "fragment.txt");

	// Projection
	//glm::mat4 proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 proj = glm::ortho(0, 2, 2, 0);
	shader.Enable();
	shader.UniformMat4x4("projection", proj);

	float ticker = 0;

	//glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (window.IsOpen()) {
	
		// Input here
		for(auto _event : window.GetEvents()){

		}
		window.FlushEvents();

		// Program logic
		
		// Send a translation matrix to the shader!
		float s = 1.0f;
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), (ticker), glm::vec3(0, 1, 1));
		glm::mat4 scale = glm::scale(glm::mat4(1.0), glm::vec3(1.0f*s, 1.0f*s, 1.0f*s));

		auto res = scale * translate;

		shader.UniformMat4x4("model", res);

		// Render starts here
		shader.Enable();
		window.Clear({0.15f, 0.15f, 0.15f});
		
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 3*4, GL_UNSIGNED_INT, 0);

		window.Display();

		ticker += 0.02f;
	}
	
	// Close the DebugLog file! (not really needed)
	terr::DebugLog::CloseDebugLog();
	// Important call!
	terr::Config::ClearAllocatedMemory();
}