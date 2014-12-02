#pragma once

#include "defines.h"
#include "Window.h"

#include <vector>


namespace pv
{
	class PAAVO_EXPORT Sprite
	{
	public:
		Sprite();
		Sprite(float x, float y, float width, float height, pv::Window& window);
		void setTexture(std::string filename);
		~Sprite();
		void setPosition(float x, float y);
		void move(float x, float y);
		void draw();
		float getX(){ return _x + _offX; }
		float getY(){ return _y + _offY; }

	private:
		std::vector<float> _vertices;
		std::vector<unsigned int> _elements;

		float _x;
		float _y;
		float _width;
		float _height;
		float _size;
		float _offX;
		float _offY;

		unsigned int _vbo;
		unsigned int _ebo;
		unsigned int _texId;
		unsigned int _texBool;
		int _posAttrib;
		int _colAttrib;
		int _texAttrib;
		int _offsetUnif;


		Window& _win;
	};

} // namespace pv
