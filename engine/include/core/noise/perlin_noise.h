#pragma once

typedef unsigned int uint;

#include<glm/vec3.hpp>
#include<vector>

namespace terr {

	// This was obtained as a translation from the original "improved noise"
	// Se länk: http://mrl.nyu.edu/~perlin/noise/
	// Original copyright 2002 Ken Perlin

	class PerlinNoise3D {
	public:
		PerlinNoise3D();

		// Generates the permutation vector, gets called by constructor
		void GeneratePermutationVector(uint seed);

		// Hämta noise värden 
		double Evaluate(glm::vec3 pos);

	private:
		double fade(double t);
		double lerp(double t, double i, double j);
		double grad(int hash, double x, double y, double z);

		std::vector<uint> p;
	};

}