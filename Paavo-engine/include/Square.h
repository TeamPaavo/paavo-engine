#pragma once
#include "defines.h"
#include "Window.h"

namespace pv
{
	namespace Primitive
	{
		class PAAVO_EXPORT Square
		{
		public:
			Square(float size, float x, float y, Window &window);
			~Square(); 
			void draw();

		private:
			std::vector<float> _vertices;
			std::vector<unsigned int> _elements;

			float _x;
			float _y;
			float _size;

			unsigned int _vbo;
			unsigned int _ebo;

			int _posAttrib;
			int _colAttrib;

			Window& _win;
			
		};
	}

} //namespace pv

