#include"../include/core/noise/perlin_noise.h"

using namespace terr;

#include <cmath>
#include <random>
#include <algorithm>
#include <numeric>

PerlinNoise3D::PerlinNoise3D() {
	// Referens permutation vector tagen från original implementationen
	p = {
		151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
		8,99,37,240,21,10,23,190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
		35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,
		134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
		55,46,245,40,244,102,143,54, 65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
		18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,
		250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
		189,28,42,223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167,
		43,172,9,129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,
		97,228,251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,
		107,49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
		138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 
	};

	p.insert(p.end(), p.begin(), p.end());
}

void PerlinNoise3D::GeneratePermutationVector(uint seed) {
	p.resize(256);

	std::iota(p.begin(), p.end(), 0);
	std::default_random_engine random_engine(seed);

	std::shuffle(p.begin(), p.end(), random_engine);

	p.insert(p.end(), p.begin(), p.end());
}

double PerlinNoise3D::fade(double t) {
	// 6t^5 - 15*t^4 + 10*t^3
	return 6 * std::pow(t, 5) - 15 * std::pow(t, 4) + 10 * std::pow(t, 3);
}

// Standard linear lerping
double PerlinNoise3D::lerp(double t, double i, double j) {
	return i + t * (j - i);
}

// Magic grad function taken from sol-prog on github!
double PerlinNoise3D::grad(int hash, double x, double y, double z) {
	int h = hash & 15;
	double u = h < 8 ? x : y,
		v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double PerlinNoise3D::Evaluate(glm::vec3 pos) {
	// Find the unit cube point
	glm::vec3 POS;
	POS.x = (int)floor(pos.x) & 255;
	POS.y = (int)floor(pos.y) & 255;
	POS.z = (int)floor(pos.z) & 255;

	// Find the releveant x,y,z inside the unit cube
	pos.x -= floor(pos.x);
	pos.y -= floor(pos.y);
	pos.z -= floor(pos.z);

	// Compute curves using fade for each coord position
	auto u = fade(pos.x);
	auto v = fade(pos.y);
	auto w = fade(pos.z);

	// Hash coordinates of the cube corners
	int A = p[POS.x] + POS.y;
	int AA = p[A] + POS.z;
	int AB = p[A + 1] + POS.z;
	int B = p[POS.x + 1] + POS.y;
	int BA = p[B] + POS.z;
	int BB = p[B + 1] + POS.z;

	// Final add blended results from each cube corner
	double res = lerp(w, lerp(v, lerp(u, grad(p[AA], pos.x, pos.y, pos.z), grad(p[BA], pos.x - 1, pos.y, pos.z)), lerp(u, grad(p[AB], pos.x, pos.y - 1, pos.z), grad(p[BB], pos.x - 1, pos.y - 1, pos.z))), lerp(v, lerp(u, grad(p[AA + 1], pos.x, pos.y, pos.z - 1), grad(p[BA + 1], pos.x - 1, pos.y, pos.z - 1)), lerp(u, grad(p[AB + 1], pos.x, pos.y - 1, pos.z - 1), grad(p[BB + 1], pos.x - 1, pos.y - 1, pos.z - 1))));
	return (res + 1.0) / 2.0;
}