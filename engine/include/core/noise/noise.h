#include <cstdlib>
#include <iostream>
#include <vector>

namespace terr {

	class Noise {

	public:
		static std::vector<float> Generate(int size = 64);
	};

}