#include "..\include\Camera.h"

using namespace pv;

Camera::Camera(GLuint programId)
{
	_programId = programId;

	_viewIndex = glGetUniformLocation(_programId, "view");
	assert(_viewIndex != -1);
}	

void Camera::moveCamera(GLfloat x, GLfloat y)
{
	_viewTransform = glm::translate(vec3(x, y, 0));
	glUniformMatrix4fv(_viewIndex, 1, GL_FALSE, reinterpret_cast<float*>(&_viewTransform));
}

Camera::~Camera()
{
}
