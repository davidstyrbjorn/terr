#include"../include/core/camera.h"
#include<glm/gtc/matrix_transform.hpp>

glm::mat4& terr::Camera::GetViewMatrix()
{
	return view_matrix;
}

void Update(float dt){
	view_matrix = glm::
}
