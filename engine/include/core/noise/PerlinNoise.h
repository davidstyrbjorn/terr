#include <vector>

namespace terr {

	class PerlinNoise {

	public:

		static std::vector<float> Generate(int nWidth, int nHeight, float* fSeed, int nOctaves, float fBias, float* fOutput);

		//static float Evaluate(int width, int weight, std::vector<float> noiseSeed, int OctaveCount, float ScalingBias, fPerlinNoise2D);
	};

}