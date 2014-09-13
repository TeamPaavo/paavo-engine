#include "..\include\Window.h"

using namespace pv;

Window::Window()
{
	_isOpen = false;
	_winClassName = L"Paavo-engine-window";
}


Window::~Window()
{
	printf("Menin kiinni, oho %s\n", _winTitle.c_str());
}

bool Window::create(const std::wstring& title, int width, int height)
{
	_winTitle = title;
	_winWidth = width;
	_winHeight = height;
	
	return _createWindow();
}

bool Window::isOpen()
{
	return _isOpen;

}

void Window::update()
{
	while (GetMessage(&_winMessage, NULL, 0, 0) > 0)
	{
		TranslateMessage(&_winMessage);
		DispatchMessage(&_winMessage);
	}
}

ATOM Window::_registerClass(HINSTANCE _instance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = &Window::_routeWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = _instance;
	wcex.hIcon = LoadIcon(_instance, IDI_ERROR);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _winClassName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_ASTERISK);

	return RegisterClassEx(&wcex);
}

BOOL Window::_createWindow()
{
	
	_winInstance = GetModuleHandle(nullptr);
	_registerClass(_winInstance);
	return _initInstance(_winInstance, 1);
}

BOOL Window::_initInstance(HINSTANCE instance, int cmdShow)
{
	HWND hwnd;

	RECT winRect;
	winRect.left = 0;
	winRect.top = 0;
	winRect.right = _winWidth;
	winRect.bottom = _winHeight;

	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	hwnd = CreateWindowW(_winClassName, (TCHAR*)_winTitle.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, winRect.right, winRect.bottom, NULL, NULL, instance, NULL);
	if (!hwnd)
		return FALSE;
	SetWindowLongPtr(hwnd, GWLP_USERDATA, (long)this);
	ShowWindow(hwnd, cmdShow);
	UpdateWindow(hwnd);
	_isOpen = true;
	return TRUE;
}

int Window::_wndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wparam);
		wmEvent = HIWORD(wparam);
	case WM_PAINT:
		hdc = BeginPaint(window, &ps);
		
		EndPaint(window, &ps);
		break;
	case WM_DESTROY:
		_isOpen = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(window, message, wparam, lparam);
	}

	return 0;
}

LRESULT CALLBACK Window::_routeWndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	Window* w = (Window*)GetWindowLongPtr(window, GWLP_USERDATA);
	if (w == NULL) {
		return DefWindowProc(window, message, wparam, lparam);
	}
	return w->_wndProc(window, message, wparam, lparam);
}