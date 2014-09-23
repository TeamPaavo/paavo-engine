#include "..\include\Window.h"
#include <gl\GL.h>

using namespace pv;

// Constructors & Destructor

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

// Public methods

bool Window::create(const std::wstring& title, int width, int height)
{
	_winTitle = title;
	_winWidth = width;
	_winHeight = height;

	return createWindow();
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

void Window::clearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swap()
{
	SwapBuffers(_hDc);
}

// Private methods

BOOL Window::createWindow()
{

	_winInstance = GetModuleHandle(nullptr);
	registerClass(_winInstance);
	return initInstance(_winInstance, 1);
}

ATOM Window::registerClass(HINSTANCE _instance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = &Window::routeWndProc;
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

BOOL Window::initInstance(HINSTANCE instance, int cmdShow)
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

	// Device hande
	_hDc = GetDC(_winHandle);

	// Set pixeformat data
	_pfd.nSize = sizeof(_pfd);
	_pfd.nVersion = 1;
	_pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	_pfd.iPixelType = PFD_TYPE_RGBA;
	_pfd.cColorBits = 24;
	_pfd.cDepthBits = 24;

	_pixelFormat = ChoosePixelFormat(_hDc, &_pfd);
	SetPixelFormat(_hDc, _pixelFormat, &_pfd);

	// Create OpenGL context
	_hGlrc = wglCreateContext(_hDc);
	wglMakeCurrent(_hDc, _hGlrc);

	SetWindowLongPtr(_winHandle, GWLP_USERDATA, (long)this);
	ShowWindow(_winHandle, cmdShow);
	UpdateWindow(_winHandle);
	return TRUE;
}

int Window::wndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
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
		wglMakeCurrent(_hDc, nullptr);
		wglDeleteContext(_hGlrc);
		PostQuitMessage(0);
		break;
	default:

		return DefWindowProc(window, message, wparam, lparam);
	}

	return 0;
}

LRESULT CALLBACK Window::routeWndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	Window* w = (Window*)GetWindowLongPtr(window, GWLP_USERDATA);
	if (w == NULL) {
		return DefWindowProc(window, message, wparam, lparam);
	}
	return w->wndProc(window, message, wparam, lparam);
}
