#include "..\include\Camera.h"

using namespace pv;

Camera::Camera(GLuint programId)
{ 

	_programId = programId;

	_viewIndex = glGetUniformLocation(_programId, "view");
	assert(_viewIndex != -1);

}	

void Camera::setCameraPosition(GLfloat xPosition, GLfloat yPosition)
{
	_viewTransform = glm::translate(glm::mat4(1.0f), vec3(xPosition, yPosition, _zAxis));
	glUniformMatrix4fv(_viewIndex, 1, GL_FALSE, reinterpret_cast<float*>(&_viewTransform));
}

void Camera::moveCamera(GLfloat xMove, GLfloat yMove)
{
	_viewTransform = glm::translate(glm::mat4(1.0f), vec3(xMove, yMove, _zAxis));

	_MVP = _viewTransform*_viewRotation;
	glUniformMatrix4fv(_viewIndex, 1, GL_FALSE, reinterpret_cast<float*>(&_MVP));
}


void Camera::rotateCamera(GLfloat rotate)
{
	_viewRotation = glm::rotate(_viewTransform, rotate, glm::vec3(0, 0, 1));

	_MVP = _viewRotation*_viewTransform;
	glUniformMatrix4fv(_viewIndex, 1, GL_FALSE, reinterpret_cast<float*>(&_MVP));
}

Camera::~Camera()
{
}
