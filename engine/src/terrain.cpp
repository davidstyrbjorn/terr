#include "..\include\core\terrain.h"

#define GLEW_STATIC
#include<GL/glew.h>

#include<cmath>

#include"../include/core/noise/approx_perlin_noise.h"
#include"../include/core/noise/perlin_noise.h"

#include"../include/imgui/imgui.h"

terr::Terrain::Terrain() :
	size(0), scale(0), vbo(0), ibo(0), vao(0), index_count(0)
{

}

terr::Terrain::~Terrain()
{
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteVertexArrays(1, &vao);
}

#include<iostream>
void terr::Terrain::ConstructTerrain(int _size, glm::vec<3, int> _scale, uint seed)
{
	//ApproxPerlinNoise perlinNoiseValues = ApproxPerlinNoise(_size, 8, 1.0f/10.0f);

	// Create perlin noise object
	perlin_noise.GeneratePermutationVector(100);
	std::vector<float> list;

	scale = _scale;
	size = _size;

	for (int z = 0; z < size; z++) {
		for (int x = 0; x < size; x++) {
			NodeData node;

			float temp = (float)x / size;
			float temp2 = (float)z / size;
			//std::cout << temp << std::endl;

			double n = perlin_noise.Evaluate({ temp*4, temp2*4, 3 });
			//n = n - floor(n);
			n = floor(255 * n);
			list.push_back(n);

			node.pos = { scale.x * (float)x, 0, scale.y * (float)z };

			nodes.push_back(node);
			starting_points.push_back(node.pos);
		}
	}

	// Create VAO
	glGenBuffers(1, &vao);
	glBindVertexArray(vao);

	// Generates IBO
	GenerateIndiciesBuffer();

	// Create VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, nodes.size() * sizeof(NodeData), &nodes.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(NodeData), (void*)0);
}

void terr::Terrain::RenderTerrain()
{
	/* GENERATEN SOME IMGUI THINGIES */ 
	ImGui::Begin("Terrain Window");
	
	// Scale input as a vec3
	ImGui::InputInt3("Scale", &scale[0]);
	
	// Seed input as unsigned integer
	int temp = (int)seed;
	ImGui::InputInt("Seed", &temp);
	seed = (uint)temp;
	
	// Buttons for various actions
	if(ImGui::Button("Generate")) {
	
	}
	ImGui::SameLine();
	if (ImGui::Button("Random Seed")) {
	
	}
	
	ImGui::End();

	//glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
}

void terr::Terrain::UpdateTerrain(float t)
{

}

void terr::Terrain::GenerateIndiciesBuffer()
{
	int squares_per_side = size - 1;
	int no_squares = std::pow(squares_per_side, 2);

	index_count = no_squares * 6; // 3 indices per triangle, 2 triangles per square

	unsigned int* indices = new unsigned int[index_count];
	int counter = 0; // Used in the index generation
	int pointer = 0; // ------||------

	for (int i = 0; i < index_count; i++) {
		int _temp = size + 1;

		indices[i] = pointer; i += 1;
		indices[i] = pointer + 1; i += 1;
		indices[i] = pointer + _temp; i += 1;
		indices[i] = pointer; i += 1;
		indices[i] = pointer + _temp; i += 1;
		indices[i] = pointer + (_temp - 1);

		counter++;

		if (counter == size - 1) {
			pointer += 2;
			counter = 0;
		}
		else {
			pointer += 1;
		}
	}

	std::vector<unsigned int> indices_vec(indices, indices + index_count);
	delete[] indices;

	// IBO
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_vec.size() * sizeof(unsigned int), &indices_vec.front(), GL_STATIC_DRAW);
}