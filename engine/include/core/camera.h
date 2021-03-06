#pragma once

#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"../core/Input.h"
#include "../core/window.h"

namespace terr {

	class Camera {
	public:
		
		void createCamera(float x, float y, float z, terr::Window* _window);
		glm::mat4& GetViewMatrix();
		
		void Update(float dt);
		void Event(terr::Event event);



	public:
		terr::Window* window;
		glm::mat4 view_matrix; // Manipulate this, view matrix is contains all the camera transformations
		glm::vec3 cam_pos;
		glm::vec3 cam_front;
		glm::vec3 cam_up;
		glm::vec3 cam_right;
		glm::vec3 world_up;

		float last_mouse_pos_x;
		float last_mouse_pos_y;

		// Euler Angles
		float yaw;
		float pitch;
		// Camera options
		float mov_speed;
		float mouse_sens;
		float zoom;
		// other
		bool lookingAround = false;

	};

}