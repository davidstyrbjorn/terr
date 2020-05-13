#include"../include/core/camera.h"
#include<glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

void terr::Camera::createCamera(float x, float y, float z, terr::Window* _window)
{
	window = _window;
	cam_pos = glm::vec3(150.0f, 150.0f, 150.0f);
	cam_front = glm::vec3(0.0f, 0.0f, -1.0f);
	cam_up = glm::vec3(0.0f, 1.0f, 0.0f);
	//view_matrix = glm::translate(glm::mat4(1.0f), -cam_pos);
    view_matrix = glm::lookAt(cam_pos, cam_front, cam_up);
}

glm::mat4& terr::Camera::GetViewMatrix()
{
	return view_matrix;
}

void terr::Camera::Update(float dt)
{
    float cam_speed = 100.0f;
	// Translate the view matrix
	//view_matrix = glm::translate(glm::mat4(1.0f), -cam_pos);
    view_matrix = glm::lookAt( cam_pos, cam_front, cam_up);
    //WASD moves camera
    if (window->IsKeyDown(TERR_KEY_W)) {
        cam_pos.z -= cam_speed * dt;
    }
    if (window->IsKeyDown(TERR_KEY_A)) {
        cam_pos.x -= cam_speed * dt;
    }
    if (window->IsKeyDown(TERR_KEY_S)) {
        cam_pos.z += cam_speed * dt;
    }
    if (window->IsKeyDown(TERR_KEY_D)) {
        cam_pos.x += cam_speed * dt;
    }

}

void terr::Camera::Event(terr::Event event)
{
    /*event.key
    const float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;*/
}
