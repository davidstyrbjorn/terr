#include"../include/core/window.h"

#include"../include/core/debug_log.h"
#include"../include/core/config.h"
#include"../include/core/clock.h"
#include"../include/core/vec3.h"
#include"../include/core/color.h"
#include"../include/core/Input.h"

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

typedef unsigned int uint;

uint load_shaders(const char* vertex_path, const char* frag_path) {
	uint vertex_id = glCreateShader(GL_VERTEX_SHADER);
	uint fragment_id = glCreateShader(GL_FRAGMENT_SHADER);

	// Read vertex shader code from the file with the given path
	std::string vertex_shader_code;
	std::ifstream ifstream(vertex_path, std::ios::in);
	if (ifstream.is_open()) {
		std::stringstream sstr;
		sstr << ifstream.rdbuf();
		vertex_shader_code = sstr.str();
		ifstream.close();
	}
	else {
		std::cout << "VERTEX: Can't open vertex shader code file!!!" << std::endl;
	}

	std::string fragment_shader_code;
	ifstream.open(frag_path, std::ios::in);
	if (ifstream.is_open()) {
		std::stringstream sstr;
		sstr << ifstream.rdbuf();
		fragment_shader_code = sstr.str();
		ifstream.close();
	}
	else {
		std::cout << "FRAGMENT: Can't open fragment shader code file!!!" << std::endl;
	}

	// Helpers
	int info_log_length;

	// Compile the vertex & fragment shaders!
	char const* vertex_c_str = vertex_shader_code.c_str();
	glShaderSource(vertex_id, 1, &vertex_c_str, NULL);
	glCompileShader(vertex_id);
	// Check for error
	glGetShaderiv(vertex_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0) {
		std::vector<char> vertex_shader_error_message(info_log_length + 1);
		glGetShaderInfoLog(vertex_id, info_log_length, NULL, &vertex_shader_error_message[0]);
		printf("VERTEX: %s\n", &vertex_shader_error_message[0]);
	}

	char const* frag_c_str = fragment_shader_code.c_str();
	glShaderSource(fragment_id, 1, &frag_c_str, NULL);
	glCompileShader(fragment_id);
	// Check for error
	glGetShaderiv(fragment_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0) {
		std::vector<char> fragment_shader_error_message(info_log_length + 1);
		glGetShaderInfoLog(fragment_id, info_log_length, NULL, &fragment_shader_error_message[0]);
		printf("FRAGMENT: %s\n", &fragment_shader_error_message[0]);
	}

	// Link the shader program
	uint program_id = glCreateProgram();
	glAttachShader(program_id, vertex_id);
	glAttachShader(program_id, fragment_id);
	glLinkProgram(program_id);

	glDetachShader(program_id, vertex_id);
	glDetachShader(program_id, fragment_id);

	glDeleteShader(vertex_id); glDeleteShader(fragment_id);

	return program_id;
}

int main() {

	// This goes through the config files and gets the data 
	terr::Config::ParseFromConfigFile();

	// Open the DebugLog file
	terr::DebugLog::OpenDebugLog();

	// Create window
	terr::Window window = terr::Window(900, 630, "Terr", false);

	// GLEW init
	if (glewInit() != GLEW_OK) {
		std::cout << "glew failed to init" << std::endl;
	}

	// An array of 3 vectors which represents 3 vertices
	const float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left
	};

	const unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	// Create VAO
	unsigned int vao;
	glGenBuffers(1, &vao);
	glBindVertexArray(vao);

	// Create IBO
	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Create VBO
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	uint program_id = load_shaders("vertex.txt", "fragment.txt");

	float ticker = 0;

	while (window.IsOpen()) {
	
		// Input here
		for(auto _event : window.GetEvents()){

		}
		window.FlushEvents();

		// Program logic
		
		// Send a translation matrix to the shader!
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.5*cos(ticker*0.1f), 0.5*sin(ticker*0.1f), 0));
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), (ticker), glm::vec3(0, 0, 1));
		glm::mat4 scale = glm::scale(glm::mat4(1.0), glm::vec3(0.5f, 0.5f, 1.0f));

		uint location = glGetUniformLocation(program_id, "translate");
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(rotation*translate*scale));

		// This is a comment in my mexican accent

		// Render starts here
		glUseProgram(program_id);
		window.Clear({0.15f, 0.15f, 0.15f});
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		window.Display();

		ticker += 0.05f;
	}
	
	// Close the DebugLog file! (not really needed)
	terr::DebugLog::CloseDebugLog();
	// Important call!
	terr::Config::ClearAllocatedMemory();
}