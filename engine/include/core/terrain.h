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
		// Utility methods
		void UpdateIndicesBuffer(); // Uses nodes member as data
		void UpdateVertexBuffer(); // Uses nodes member as data
		void UpdateNodes(); // Runs the perlin-noise on all the nodes using the current parameters for generation

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
		float frequency = 1.0f;
		float noise_z = 0.0f;

		// Terrain animation info
		bool isAnimating = false;
		bool animatingFrequency = false;
		float freqAnimInterval = 5; // Animate the frequnecy between - and + this value
		float freqAnimSpeed = 0.1f;
		bool animatingNoiseZ = false;
		float noiseZAnimInterval = 1;
		float noiseZAnimSpeed = 0.1f;
		float animTicker = 0.0f;
	};
}