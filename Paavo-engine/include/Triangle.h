#pragma once
#include "defines.h"
#include "Window.h"

namespace pv
{
	namespace Primitive
	{
		class PAAVO_EXPORT Triangle
		{
		public:
			Triangle(float size, float x, float y, Window &window);
			~Triangle();
			void draw();
			void move(float x, float y);
			void setPosition(float x, float y);

		private:
			std::vector<float> _vertices;
			std::vector<unsigned int> _elements;

			float _x;
			float _y;
			float _size;
			float _offX;
			float _offY;

			unsigned int _vbo;
			unsigned int _ebo;

			int _posAttrib;
			int _colAttrib;
			int _offsetUnif;

			Window& _win;
		};
		
	}

}//namespace pv
