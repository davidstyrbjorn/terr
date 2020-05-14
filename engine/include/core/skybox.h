#pragma once

#include<string>
#include<vector>

namespace terr {

	class Skybox {
	public:
		Skybox();

		void CreateSkybox();

	public:
		unsigned int textureID;
		unsigned int vao, vbo;
	};

}