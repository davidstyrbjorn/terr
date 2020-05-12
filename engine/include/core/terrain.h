#include<vector>
#include<glm/vec3.hpp>

#define PI 3.14159265359f

namespace terr {
	
	struct NodeData {
		glm::vec3 pos;
	};

	struct Vertex;

	class Terrain {
	public:
		Terrain();
		~Terrain();

		void ConstructTerrain(int _size, float _scale);
		void RenderTerrain();
		void UpdateTerrain(float t);

		int size;
		float scale;
		unsigned int vbo, ibo;
		unsigned int vao;
		int index_count;
		std::vector<NodeData> nodes;
		std::vector<glm::vec3> starting_points;
	};
}