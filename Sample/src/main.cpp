#include "Window.h"
#include "Rect.h"

#include <GL\glew.h>
#include "..\FreeImage\Dist\FreeImage.h"

int main()
{
	pv::Window win("Otsikko", 800, 600);

	pv::Rect sprite(-0.5f, 0.5f, 1.0f, 1.0f, win);
	pv::Rect sprite2(-1.0f, 1.0f, 0.5f, 0.5f, win);

	while (win.update()){
		win.clearColor(0.2f, 0.2f, 0.2f, 1.0f);

		sprite.draw();
		sprite2.draw();

		win.swap();
	}

	return 0;
}
