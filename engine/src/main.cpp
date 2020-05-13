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
	// Använder PerlinNoise klassen
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

		terrain.ConstructTerrain(32, 10);

		// Projection matrix
		glm::mat4 proj = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.001f, 2000.0f);

		shader.Enable();
		shader.UniformMat4x4("projection", proj);
	}

	void OnUserUpdate(float dt) override {
		// Update camera
		//camera.Update(dt);
	}

	void OnUserRender() override {

		ImGui::Begin("test");
		ImGui::End();

		auto in_color = glm::vec3(sin(t*0.01), 1, 0);

		// Send shit to the shader
		shader.UniformFloat("scale", terrain.scale); // Temporary
		shader.UniformVec3("in_color", in_color); // Sending color to fragment shader
		shader.UniformMat4x4("view_matrix", camera.GetViewMatrix()); // Send the camera matrix

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

private:
	terr::Shader shader;
	terr::Terrain terrain;
	terr::Camera camera;

};

int main() {
	App app = App();
	app.CreateWindow(1200, 800);



	return 0;
}