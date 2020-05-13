#pragma once

typedef unsigned int uint;

#include<glm/vec3.hpp>
#include<vector>

namespace terr {

	// This was obtained as a translation from the original "improved noise"
	// Se l�nk: http://mrl.nyu.edu/~perlin/noise/
	// Original copyright 2002 Ken Perlin

	class PerlinNoise3D {
	public:
		// Init med reference v�rden f�r permutations vektorn/listan
		PerlinNoise3D();

		// Init med seed f�r att skapa permutations vektorn
		PerlinNoise3D(uint seed);

		// H�mta noise v�rden 
		double noise(glm::vec3 pos);

	private:
		double fade(double t);
		double lerp(double t, double i, double j);
		double grad(int hash, double x, double y, double z);

		std::vector<uint> p;
	};

}