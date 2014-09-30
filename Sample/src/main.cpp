#include "Window.h"

int main()
{
	pv::Window win(L"Otsikko", 800, 600);

	while (win.update()){
		win.clearColor(1.0f, 0.0f, 0.0f, 1.0f);
		win.draw();
		win.swap();
	}

	return 0;
}
