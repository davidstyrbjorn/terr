#pragma once

typedef unsigned int uint;

#include<string>

#include<glm/vec3.hpp>
#include<glm/mat4x4.hpp>

namespace terr {

	class Shader {
	public:
		// Constructor
		Shader() { }
		// Destructor
		~Shader();

		/* Public methods */

		void CreateShader(std::string vertex_file_path, std::string fragment_file_path);

		void Enable();
		void Disable();

		void UniformMat4x4(std::string name, const glm::mat4x4& mat);
		void UniformVec3(std::string name, const glm::vec3& vec);

	private:
		uint GetUniformLocation(std::string name);

	private:
		uint program_id; // opengl connection
	};

}