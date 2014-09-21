#include "..\include\Window.h"

using namespace pv;

Window::Window()
{
	_winClassName = L"Paavo-engine-window";
}

Window::Window(const std::wstring& title, int width, int height)
{
	_winClassName = L"Paavo-engine-window";
	create(title, width, height);
}


Window::~Window()
{

}

bool Window::create(const std::wstring& title, int width, int height)
{
	_winTitle = title;
	_winWidth = width;
	_winHeight = height;

	return _createWindow();
}

bool Window::update()
{
	while (PeekMessageW(&_winMessage, NULL, 0, 0, PM_REMOVE) > 0)
	{
		if (_winMessage.message == WM_QUIT)
			return false;
		TranslateMessage(&_winMessage);
		DispatchMessage(&_winMessage);
	}
	return true;
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

	RECT winRect;
	winRect.left = 0;
	winRect.top = 0;
	winRect.right = _winWidth;
	winRect.bottom = _winHeight;

	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	_winHandle = CreateWindowW(_winClassName, (TCHAR*)_winTitle.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, winRect.right, winRect.bottom, NULL, NULL, instance, NULL);
	if (!_winHandle)
		return FALSE;
	SetWindowLongPtr(_winHandle, GWLP_USERDATA, (long)this);
	ShowWindow(_winHandle, cmdShow);
	UpdateWindow(_winHandle);
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
