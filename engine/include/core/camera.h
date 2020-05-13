#pragma once

#include<glm/mat4x4.hpp>
#include"../core/Input.h"
#include"../core/window.h"

namespace terr {

	class Camera {
	public:
		glm::mat4& GetViewMatrix();
		
		void Update(float dt);
		void Event(terr::Event event);

	private:
		glm::mat4 view_matrix; // Manipulate this, view matrix is contains all the camera transformations
		glm::vec3 cam_pos;
		terr::Window window;
	};

}