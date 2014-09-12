#include "Window.h"

int main()
{
	pv::Window win;
	win.create("Otsikko", 300, 300);
	
	while (win.isOpen())
	{
		win.update();
	}

	return 0;
}