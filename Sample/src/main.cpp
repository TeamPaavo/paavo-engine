#include "Window.h"
#include <assert.h>

int main()
{
	pv::Window win(L"Äö", 800, 600);

	assert(true);

	while (win.update()){

	}

	return 0;
}
