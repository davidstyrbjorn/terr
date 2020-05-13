#include"../include/core/camera.h"

void terr::Camera::createCamera(float x, float y, float z, terr::Window* _window)
{
	window = _window;
	cam_pos = glm::vec3(150.0f, 150.0f, -150.0f);
	cam_front = glm::vec3(0.0f, 0.0f, -1.0f);
	cam_up = glm::vec3(0.0f, 1.0f, 0.0f);
	view_matrix = glm::translate(glm::mat4(1.0f), cam_pos);

}

glm::mat4& terr::Camera::GetViewMatrix()
{
	return view_matrix;
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
