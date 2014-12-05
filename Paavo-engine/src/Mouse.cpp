#include "..\include\Mouse.h"


Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}

POINT Mouse::checkpos()
{
	GetCursorPos(&p);
	return p;

	/*mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); // Left click Down
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0); // Left click Down
	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0); // Left click Down
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0); // Left click Down*/

}
