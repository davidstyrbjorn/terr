#include"../include/core/camera.h"
#include<glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <string>

void terr::Camera::createCamera(float x, float y, float z, terr::Window* _window)
{
	window = _window;
	cam_pos = glm::vec3(window->width/2, 150.0f, 1700.0f);
	cam_front = glm::vec3(0.0f, 0.0f, -1.0f);
    cam_right = glm::vec3(1.0f, 0.0f, 0.0f);
	cam_up = glm::vec3(0.0f, 1.0f, 0.0f);
    world_up = cam_up;
	//view_matrix = glm::translate(glm::mat4(1.0f), -cam_pos);
    view_matrix = glm::lookAt(cam_pos, cam_pos + cam_front, cam_up);
    
    last_mouse_pos_x = window->mouse_x;
    last_mouse_pos_y = window->mouse_y;

    yaw = -90.0f;
    pitch = 0.0f;
    
    mov_speed = 100.0f;
    mouse_sens = 0.1f;
    zoom = 45.0f;
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
    view_matrix = glm::lookAt( cam_pos, cam_pos + cam_front, cam_up);
    //WASD moves camera
    float velocity = mov_speed *  dt;
    if (window->IsKeyDown(TERR_KEY_W)) {
        cam_pos += cam_front * velocity;
    }
    if (window->IsKeyDown(TERR_KEY_A)) {
        cam_pos -= cam_right * velocity;
    }
    if (window->IsKeyDown(TERR_KEY_S)) {
        cam_pos -= cam_front * velocity;
    }
    if (window->IsKeyDown(TERR_KEY_D)) {
        cam_pos += cam_right * velocity;
    }
    if (window->IsKeyDown(TERR_KEY_SPACE)) {
        cam_pos += cam_up * velocity;
    }
    if (window->IsKeyDown(TERR_KEY_LEFT_CONTROL)) {
        cam_pos -= cam_up * velocity;
    }
    //rotates camera with mouse
    if (last_mouse_pos_x != window->mouse_x || last_mouse_pos_y != window->mouse_y) {
        float xoffset = window->mouse_x - last_mouse_pos_x;
        float yoffset = window->mouse_y - last_mouse_pos_y;
        last_mouse_pos_x = window->mouse_x;
        last_mouse_pos_y = window->mouse_y;

        float sensitivity = 0.05;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(-pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cam_front = glm::normalize(direction);

        //re-calculate the Right and Up vector
        cam_right = glm::normalize(glm::cross(cam_front, world_up));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        cam_up = glm::normalize(glm::cross(cam_right, cam_front));
        
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
