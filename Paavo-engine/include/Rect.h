#pragma once

#include "defines.h"
#include "Window.h"

#include <vector>


namespace pv
{
	class PAAVO_EXPORT Rect
	{
	public:
		Rect();
		Rect(float x, float y, float width, float height, pv::Window& window);
		~Rect();

		void draw();

	private:
		std::vector<float> _vertices;
		std::vector<unsigned int> _elements;

		float _x;
		float _y;
		float _width;
		float _height;

		unsigned int _vbo;
		unsigned int _ebo;
		unsigned int _texId;

		int _posAttrib;
		int _colAttrib;
		int _texAttrib;

		Window& _win;
	};

} // namespace pv