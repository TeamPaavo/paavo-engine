#pragma once

#include <iostream>
#include <GL\glew.h>
#include <assert.h>
#include <glm\glm.hpp>


namespace pv 
{
	class Shader
	{
	public:
		Shader();

		/**
		* Constructor overload. Load shaders from file.
		* This method also compiles and links shaders to program.
		*
		* @param	vertexFileName	Path to vertex shader.
		* @param	fragmentFileName	Path to fragment shader.
		*/
		Shader(const std::string& vertexFileName, const std::string& fragmentFileName);

		~Shader();

		/**
		 * Load shaders from file.
		 * This method also compiles and links shaders to program.
		 *
		 * @param	vertexFileName	Path to vertex shader.
		 * @param	fragmentFileName	Path to fragment shader.
		 * @return	True if success, false if file not found or otherwise unavailable.
		 */
		bool load(const std::string& vertexFileName, const std::string& fragmentFileName);

		/**
		 * Sets shader program active.
		 */
		void use(glm::mat4 projection);

		void use();

		GLuint getProgram();

	private:
		GLuint _vertexShaderId;
		GLuint _fragmentShaderId;
		GLuint _programId;
		GLint _projectionId;

	};

} // namespace pv