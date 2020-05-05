#include <vector>


namespace terr {

	class ApproxPerlinNoise {

	public:
		static std::vector<float> Generate(int nSize, int nOctaves, float fBias);
	};

}