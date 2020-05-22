#include "..\include\core\terrain.h"

#define GLEW_STATIC
#include<GL/glew.h>

#include<glm/gtx/normal.hpp>

#include<cmath>
#include<time.h>
#include<algorithm>

#include"../include/core/noise/approx_perlin_noise.h"
#include"../include/core/noise/perlin_noise.h"

#include"../include/imgui/imgui.h"

static void NodeNormal(terr::NodeData& node, const terr::NodeData& node1, const terr::NodeData& node2) {
	node.normal = glm::normalize(glm::triangleNormal(node.pos, node2.pos, node1.pos));
}

terr::Terrain::Terrain() :
	size(0), scale(0), vbo(0), ibo(0), vao(0), index_count(0), gradient_color_count(3)
{
	gradient_colors = {
		glm::vec3(242 / 256.0f, 211 / 256.0f, 153 / 256.0f),
		glm::vec3(89 / 256.0f,68 / 256.0f, 49 / 256.0f),
		glm::vec3(166 / 256.0f,87 / 256.0f, 41 / 256.0f),
		glm::vec3(192 / 256.0f,222 / 256.0f, 136 / 256.0f),
		glm::vec3(92 / 256.0f,163 / 256.0f, 111 / 256.0f),
		glm::vec3(38 / 256.0f,91 / 256.0f,64 / 256.0f),
		glm::vec3(15 / 256.0f,62 / 256.0f,57 / 256.0f),
		glm::vec3(13 / 256.0f,33 / 256.0f,39 / 256.0f)
	};
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
	scale = _scale;
	size = _size;

	// Fills the nodes list correctly
	UpdateNodes();

	// Create VAO
	glGenBuffers(1, &vao);
	glBindVertexArray(vao);

	// Generates IBO
	glGenBuffers(1, &ibo);
	UpdateIndicesBuffer();

	// Create VBO
	glGenBuffers(1, &vbo);
	UpdateVertexBuffer();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(NodeData), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(NodeData), (GLvoid*)offsetof(NodeData, normal));

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	// WE DO NOT UNBIND IBO!!! IT IS TIED HARD TO THE VAO
}

void terr::Terrain::RenderTerrain()
{
	//glBindVertexArray(terrain.vao);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	//glBindVertexArray(vao);
	if(wireFrameOn) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, (const void*)0);
	if(wireFrameOn) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	/* GENERATEN SOME IMGUI THINGIES */ 
	ImGui::Begin("Terrain Window");
	
	ImGui::Text("Grid Data");
	// Scale input as a vec3
	ImGui::InputInt3("Scale", &scale[0]);
	// Grid size
	ImGui::InputInt("Grid Size", &size);

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	ImGui::Text("Perlin Noise Data");
	// Seed input as unsigned integer
	int temp = (int)seed;
	ImGui::DragInt("Seed", &temp, 0);
	seed = (uint)temp;
	// Frequency
	ImGui::DragFloat("Frequency", &frequency, 0.1f, 0.001f);
	// Z position
	ImGui::DragFloat("Noise Z", &noise_z, 0.1f, 0.0f);
	// Wireframe
	ImGui::Checkbox("Wireframe", &wireFrameOn);

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	ImGui::Text("Terrain Color");
	static bool selected[8] = { true, false, false, false, false, false, false, false };
	ImGui::DragInt("Gradient Count", &gradient_color_count, 1, 2, 8, "%.f");
	for (int i = 0; i < gradient_color_count; i++) {
		ImGui::PushID(i);
		ImGui::ColorEdit3("", &gradient_colors.at(i)[0]);
		ImGui::PopID();
	}

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	ImGui::Checkbox("Animate", &isAnimating);

	if (isAnimating) {
		ImGui::Text("Animation Data");
		ImGui::Checkbox("Animate Frequency", &animatingFrequency);

		ImGui::DragFloat("Freq animation interval", &freqAnimInterval, 0.1f, 0.1f);
		if (ImGui::IsItemHovered()) {
			ImGui::BeginTooltip();
			ImGui::SetTooltip("Animate the frequnecy between -interval to + interval");
			ImGui::EndTooltip();
		}
		ImGui::DragFloat("Freq animation speed", &freqAnimSpeed, 0.1f, 0.01f);

		ImGui::Checkbox("Animate Noise Z", &animatingNoiseZ);
		ImGui::DragFloat("Noise Z animation interval", &noiseZAnimInterval, 0.1f, 0.1f);
		ImGui::DragFloat("Noise Z animation speed", &noiseZAnimSpeed, 0.1f, 0.1f);
	}

	if (!isAnimating) {
		// Buttons for various actions
		if (ImGui::Button("Generate")) {
			UpdateNodes();
			UpdateIndicesBuffer();
			UpdateVertexBuffer();
		}
		ImGui::SameLine();
		if (ImGui::Button("Random Seed")) {
			srand(time(NULL));
			seed = static_cast<uint>(rand());
		}
	}
	
	ImGui::End();

}						

void terr::Terrain::UpdateTerrain(float t)
{
	if (isAnimating) {
		animTicker += 0.1f * t;
		if (animatingFrequency) {
			frequency = sin(animTicker * freqAnimSpeed) * freqAnimInterval;
		}
		if (animatingNoiseZ) {
			noise_z = std::pow((sin(animTicker * noiseZAnimSpeed / 2)), 2) * noiseZAnimInterval;
		}

		UpdateNodes();
		UpdateVertexBuffer();

	}
}

void terr::Terrain::UpdateIndicesBuffer()
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

	// Update the IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_vec.size() * sizeof(unsigned int), &indices_vec.front(), GL_STATIC_DRAW);
}

void terr::Terrain::UpdateVertexBuffer()
{
	for (int i = 0; i < index_count; i += 3) {

	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, nodes.size() * sizeof(NodeData), &nodes.front(), GL_STATIC_DRAW);
}

void terr::Terrain::UpdateNodes()
{
	// Create perlin noise object
	perlin_noise.GeneratePermutationVector(seed);
	std::vector<float> list;

	nodes.clear();
	starting_points.clear();

	for (int z = 0; z < size; z++) {
		for (int x = 0; x < size; x++) {
			NodeData node;

			// Normalize the values for the noise evalations
			float norm_x = (float)x / size;
			float norm_y = (float)z / size;

			double n = perlin_noise.Evaluate({ norm_x * frequency, norm_y * frequency, noise_z });
			//n = n - floor(n);
			n = floor(255 * n) / 255.0f;
			list.push_back(n);

			node.pos = { scale.x * (float)x, scale.y * n, scale.z * (float)z };

			nodes.push_back(node);
			starting_points.push_back(node.pos);
		}
	}

	int offset1 = 1;
	int offset2 = 4;
	int counter1 = 0;

	for (int i = 0; i < nodes.size(); i++) {
		NodeData node1 = { {0,0,0}, {0,0,0} };
		NodeData node2 = { {0,0,0}, {0,0,0} };

		// We're on the last row
		counter1++;
		if (i >= size*size - size) {
			// Last node on the column
			if (counter1 == size) {
				counter1 = 0;
				node1 = nodes[i - 1];
				node2 = nodes[i - size];
			}
			else {
				node2 = nodes[i + 1];
				node1 = nodes[i - size];
			}
		}
		else {
			// Last node on the column
			if (counter1 == size) {
				counter1 = 0;
				node2 = nodes[i - 1];
				node1 = nodes[i + size];
			}
			else {
				// We're not on the last row
				node1 = nodes[i + 1];
				node2 = nodes[i + size];
			}
		}

		NodeNormal(nodes[i], node1, node2);

	}

	max = *std::max_element(list.begin(), list.end());
	min = *std::min_element(list.begin(), list.end());
}