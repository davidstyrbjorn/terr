#include <vector>


namespace terr {

	class ApproxPerlinNoise {

	public:

		ApproxPerlinNoise(int nSize, int nOctaves, float fBias);
		
		float Evaluate(int x, int z, int size);

	private:
		std::vector<float> noise;

	};

}