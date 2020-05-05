#include "..\include\core\noise\approx_perlin_noise.h"

namespace terr {
	
	struct Vertex;

	class Terrain {
	public:
		Terrain(int _size, float _scale);
		~Terrain();

		void ConstructTerrain();
		void RenderTerrain();

	private:
		int size;
		float scale;
		unsigned int vbo, ibo;
		unsigned int vao;
		int index_count;
	};
}