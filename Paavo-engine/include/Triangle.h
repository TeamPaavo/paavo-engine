#pragma once

#include "defines.h"
#include "Window.h"

#include <vector>

namespace pv
{
	class PAAVO_EXPORT Triangle
	{
	public:
		Triangle();
		Triangle(float x, float y, float leftLeg, float rightLeg, float base, pv::Window& window);
		~Triangle();
		
		void draw();

	private:
		std::vector<float> _vertices;
		std::vector<unsigned int> _elements;

		float _x;
		float _y;
		float _leftLeg;
		float _rightLeg;
		float _base;

		unsigned int _vbo;
		unsigned int _ebo;
		unsigned int _texId;

		int _posAttrib;
		int _colAttrib;
		int _texAttrib;

		Window& _win;
	};
}
