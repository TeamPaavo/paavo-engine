#include "Window.h"
#include "Rect.h"
#include "Triangle.h"

#include <GL\glew.h>
#include "..\FreeImage\Dist\FreeImage.h"

int main()
{
	pv::Window win("Otsikko", 800, 600);

	//pv::Rect sprite(-0.5f, 0.5f, 1.0f, 1.0f, win);
	pv::Rect sprite2(200, 100, 100, 100, win);
	//pv::Triangle sprite3(300, 100, 100, 100, 100, win);

	while (win.update()){
		win.clearColor(0.2f, 0.2f, 0.2f, 1.0f);
		sprite2.draw();
		//sprite3.draw();


		//window.getInput(input);
		//if (input == enum_aerrow_dowm)
		//	blockinson.move(left);

		win.swap();
	}

	return 0;
}
