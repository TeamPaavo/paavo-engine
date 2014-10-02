#pragma once

#include "defines.h"


namespace pv
{

	class Vertex
	{
	public:
		Vertex();
		Vertex(const vec3& pos, const vec4& col, const vec2& tex);
		~Vertex();

		vec3 position;
		vec4 colour;
		vec2 texture;
	};

} // namespace pv