#pragma once

namespace terr {

	class PerlinNoise {

	public:
		// Om vi lägger till extra parametrar, ge dem standardvärden t.ex int octaves = 4! (:
		static float Evaluate(float x, float y);
	};

}