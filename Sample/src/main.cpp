#include "Window.h"

int main()
{
	pv::Window win;
	win.create(L"�tsikk�", 300, 300);

	while (win.isOpen())
	{
		win.update();
	}

	return 0;
}