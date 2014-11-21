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

		void moveCamera(GLfloat x, GLfloat y);

		~Camera();

	private:

		GLuint _programId;
		GLint _viewIndex;
		glm::mat4 _viewTransform;


	};

} //namespave pv