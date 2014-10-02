#pragma once

#include "Rect.h"

namespace pv
{

	class Sprite
	{
	public:
		Sprite();
		~Sprite();
	private:
		Rect _rect;
	};

} // namespace pv