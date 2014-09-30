#pragma once

#include <iostream>
#include <GL\glew.h>

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
		void use();

		GLuint getProgram();

	private:
		GLuint _vertexShaderId;
		GLuint _fragmentShaderId;
		GLuint _programId;

	};

} // namespace pv