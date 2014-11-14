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
			void move(float x, float y);
			void setPosition(float x, float y);
			void setColor(float r, float g, float b);

		private:
			std::vector<float> _vertices;
			std::vector<unsigned int> _elements;

			float _x;
			float _y;
			float _size;
			float _offX;
			float _offY;
			float _r;
			float _g;
			float _b;

			unsigned int _vbo;
			unsigned int _ebo;

			int _posAttrib;
			int _colAttrib;
			int _offsetUnif;
			int _colUnif;

			Window& _win;
			
		};
	}

} //namespace pv

