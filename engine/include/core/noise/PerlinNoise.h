#pragma once

namespace terr {

	class PerlinNoise {

	public:
		// Om vi l�gger till extra parametrar, ge dem standardv�rden t.ex int octaves = 4! (:
		static float Evaluate(float x, float y);
	};

}