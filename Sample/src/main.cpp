#include "Window.h"

int main()
{
	pv::Window win;
	win.create(L"Ötsikkö", 300, 300);

	while (win.isOpen())
	{
		win.update();
	}

	return 0;
}