#include<vector>
#include<glm/vec3.hpp>

#include"noise/perlin_noise.h"

#define PI 3.14159265359f

namespace terr {
	
	struct NodeData {
		glm::vec3 pos;
	};

	struct Vertex;

	class Terrain {
	private:
		// Helper methods
		void GenerateIndiciesBuffer();
		void UpdateVertexBuffer(); // Uses nodes member as data

	public:
		Terrain();
		~Terrain();

		void ConstructTerrain(int _size, glm::vec<3, int> _scale, uint seed);
		void RenderTerrain();
		void UpdateTerrain(float t);
		
		// OpenGL related
		unsigned int vbo, ibo;
		unsigned int vao;
		int index_count;

		// Terrain data
		int size;
		glm::vec<3, int> scale;
		std::vector<NodeData> nodes;
		std::vector<glm::vec3> starting_points;
		uint seed;
		PerlinNoise3D perlin_noise;
	};
}