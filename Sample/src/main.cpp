#include "Window.h"

int main()
{
	pv::Window win;
	win.create(L"�tsikk�", 300, 300);

	pv::Window win2;
	win2.create(L"�tsikk�2", 300, 600);

	while (win.isOpen() || win2.isOpen())
	{
		if (win.isOpen())
			win.update();
		if (win2.isOpen())
			win2.update();
	}

	return 0;
}