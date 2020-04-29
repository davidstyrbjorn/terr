#include "..\include\core\terrain.h"

#define GLEW_STATIC
#include<GL/glew.h>

#include<glm/vec3.hpp>

#include<vector>
#include<cmath>

terr::Terrain::Terrain(int _size, float _scale) :
	size(_size), scale(_scale), vbo(0), ibo(0), vao(0), index_count(0)
{

}

terr::Terrain::~Terrain()
{
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteVertexArrays(1, &vao);
}

void terr::Terrain::ConstructTerrain()
{
	std::vector<glm::vec3> points;

	for (int z = 0; z < size; z++) {
		for (int x = 0; x < size; x++) {
			points.push_back({ scale * (float)x, 0, scale * (float)z });
		}
	}

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

	// Create VAO
	glGenBuffers(1, &vao);
	glBindVertexArray(vao);

	// IBO
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_vec.size() * sizeof(unsigned int), &indices_vec.front(), GL_STATIC_DRAW);

	// Create VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), &points.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	

}

void terr::Terrain::RenderTerrain()
{
	//glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
}
