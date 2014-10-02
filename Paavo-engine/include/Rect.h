#pragma once

#include "Vertex.h"

namespace pv
{
	class Rect
	{
	public:
		Rect();
		~Rect();

	private:
		Vertex _vertices[4];
		float _x;
		float _y;
		float _width;
		float _height;
	};

} // namespace pv