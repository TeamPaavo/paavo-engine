#pragma once

#include "defines.h"
#include "Window.h"
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <assert.h>

namespace pv
{

	class PAAVO_EXPORT Camera
	{
	public:
		Camera(GLuint programId);

		void setCameraPosition(GLfloat xPosition, GLfloat yPosition);
		void moveCamera(GLfloat xMove, GLfloat yMove);
		void rotateCamera(GLfloat rotate);


		~Camera();

	private:

		GLuint _programId;
		GLfloat _viewIndex;

		glm::mat4 _viewTransform;
		glm::mat4 _viewRotation;
		glm::mat4 _MVP;


		//Constant values for view transforms so that the camera cannot be accidentaly broken.
		const GLfloat _zAxis = 0;
		const GLfloat _xRotation = 0;
		const GLfloat _yRotarion = 0;
		const GLfloat _zRotation = 1;


	};

} //namespave pv