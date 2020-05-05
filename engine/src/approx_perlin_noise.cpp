#include "../include/core/noise/approx_perlin_noise.h"
#include <time.h>

//nSize = 32, nOctaves = 9, fBias = 2.0f
std::vector<float> terr::ApproxPerlinNoise::Generate(int nSize, int nOctaves, float fBias) {
	
	
	std::vector<float> fOutput;
	std::vector<float> fSeed;

	

	for (int i = 0; i < nSize * nSize; i++) fSeed.push_back((float)rand() / (float)RAND_MAX);

	srand(time(NULL));

	for (int x = 0; x < nSize; x++)
		for (int y = 0; y < nSize; y++)
		{
			float fNoise = 0.0f;
			float fScaleAcc = 0.0f;
			float fScale = 1.0f;

			for (int o = 0; o < nOctaves; o++)
			{
				int nPitch = nSize * nSize >> o;
				int nSampleX1 = (x / nPitch) * nPitch;
				int nSampleY1 = (y / nPitch) * nPitch;

				int nSampleX2 = (nSampleX1 + nPitch) % nSize;
				int nSampleY2 = (nSampleY1 + nPitch) % nSize;

				float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
				float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

				float fSampleT = (1.0f - fBlendX) * fSeed[nSampleY1 * nSize + nSampleX1] + fBlendX * fSeed[nSampleY1 * nSize + nSampleX2];
				float fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * nSize + nSampleX1] + fBlendX * fSeed[nSampleY2 * nSize + nSampleX2];

				fScaleAcc += fScale;
				fNoise += (fBlendY * (fSampleB - fSampleT) + (1 - fBlendY)*fSampleT) * fScale;
				fScale = fScale / fBias; // /Fbias
			}

			// Scale to seed range
			fOutput.push_back(fNoise / fScaleAcc);
		}

	return fOutput;
}