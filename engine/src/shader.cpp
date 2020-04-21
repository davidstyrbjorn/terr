#include"../include/core/shader.h"

#define GLEW_STATIC
#include<GL/glew.h>

#include<glm/gtc/type_ptr.hpp>

#include<fstream>
#include<sstream>
#include<iostream>
#include<vector>

void terr::Shader::CreateShader(std::string vertex_file_path, std::string fragment_file_path)
{
	uint vertex_id = glCreateShader(GL_VERTEX_SHADER);
	uint fragment_id = glCreateShader(GL_FRAGMENT_SHADER);

	// Read vertex shader code from the file with the given path
	std::string vertex_shader_code;
	std::ifstream ifstream(vertex_file_path, std::ios::in);
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
	ifstream.open(fragment_file_path, std::ios::in);
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
	program_id = glCreateProgram();
	glAttachShader(program_id, vertex_id);
	glAttachShader(program_id, fragment_id);
	glLinkProgram(program_id);

	// TODO: Check if program compiled correctly!

	// We no longer have use for the individual vertex & fragment shaders!
	glDetachShader(program_id, vertex_id);
	glDetachShader(program_id, fragment_id);

	glDeleteShader(vertex_id); glDeleteShader(fragment_id);
}

terr::Shader::~Shader()
{
	glDeleteProgram(program_id);
}


void terr::Shader::Enable()
{
	glUseProgram(program_id);
}

void terr::Shader::Disable()
{
	glUseProgram(0);
}

void terr::Shader::UniformMat4x4(std::string name, const glm::mat4x4& mat)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void terr::Shader::UniformVec3(std::string name, const glm::vec3& vec)
{
	glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(vec));
}

uint terr::Shader::GetUniformLocation(std::string name)
{
	return glGetUniformLocation(program_id, name.c_str());
}
