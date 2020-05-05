#include "..\include\core\noise\noise.h"

std::vector<float> terr::Noise::Generate(int size)
{
	std::vector<float> result;

	for (int i = 0; i < size; i++) {
		result.push_back((float)std::rand());
	}


	return result;
}
