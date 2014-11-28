#pragma once

#include <glm/glm.hpp>

// API import and export
#define PAAVO_EXPORT __declspec(dllexport)
#define PAAVO_IMPORT __declspec(dllimport)

// Basic datatypes from glm
namespace pv
{
	enum KEYBOARD
	{
		DOWN,
		UP,
		LEFT,
		RIGHT,
		W,
		A,
		S,
		D,
		ESC,
		ENTER,
		NOTHING = -1
	};

	// Vectors
	typedef glm::vec2 vec2;
	typedef glm::vec3 vec3;
	typedef glm::vec4 vec4;

	// Matrices
	typedef glm::mat2x2 mat2x2;
	typedef glm::mat2x3 mat2x3;
	typedef glm::mat2x4 mat2x4;

	typedef glm::mat3x2 mat3x2;
	typedef glm::mat3x3 mat3x3;
	typedef glm::mat3x4 mat3x4;
	
	typedef glm::mat4x2 mat4x2;
	typedef glm::mat4x3 mat4x3;
	typedef glm::mat4x4 mat4x4;

} // namespace pv