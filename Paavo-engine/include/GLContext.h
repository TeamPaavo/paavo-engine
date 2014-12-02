#pragma once

#include <vector>
#include <Windows.h>
#include <GL/glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Shader.h"

namespace pv
{

	class GLContext
	{
	public:
		GLContext();
		~GLContext();

		/**
		* Initialise OpenGL context.
		*
		* @param	handle	Window handle to attach the context.
		*/
		void init(HWND handle);

		/**
		* Clear screen with color.
		* Values from 0.0 to 1.0.
		*
		* @param	r	Red
		* @param	g	Green
		* @param	b	Blue
		* @param	a	Alpha
		*/
		void clearColor(float r, float g, float b, float a);

		/**
		* Render to framebuffer
		*/
		void render(std::vector<float>& vertices, std::vector<unsigned int>& elements);

		/**
		* Swap buffers. Shows what is drawn to framebuffer.
		*/
		void swap();

		/**
		* Remove context.
		*/
		void clean();

		GLuint getDefaultTextureShader();
		GLuint getDefaultColorShader();

		void use(std::string shader);

		

	private:

		HWND _winHandle;
		HDC _hDc;
		HGLRC _hGlrc;
		PIXELFORMATDESCRIPTOR _pfd;
		int _pixelFormat;
		Shader _defaultTextureShader,_defaultColorShader;
		glm::mat4 initOrtho();

	};

} // namespace pv
