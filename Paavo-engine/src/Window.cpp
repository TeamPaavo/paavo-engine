#include "..\include\Window.h"

using namespace pv;

// Constructors & Destructor

Window::Window()
{
	_winClassName = L"Paavo-engine-window";
}

Window::Window(const std::string& title, int width, int height)
{
	_winClassName = L"Paavo-engine-window";
	create(title, width, height);
}

Window::~Window()
{
	

}

// Public methods

bool Window::create(const std::string& title, int width, int height)
{
	_winTitle = std::wstring(title.begin(),title.end());
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
	_glContext.clearColor(r, g, b, a);
}

void Window::swap()
{
	_glContext.swap();
}

void Window::draw()
{
	_glContext.render();
}

void Window::setTitle(std::string title)
{
	_winTitle = std::wstring(title.begin(), title.end());
	SetWindowText(_winHandle, _winTitle.c_str());
}

bool Window::setSize(int width, int height)
{
	_winWidth = width;
	_winHeight = height;
	return SetWindowPos(_winHandle, HWND_TOPMOST, NULL, NULL, _winWidth, _winHeight, SWP_NOMOVE);
}

void Window::close()
{
	_glContext.clean();
	PostQuitMessage(0);
}

void Window::setPosition(int x, int y)
{
	SetWindowPos(_winHandle, HWND_TOPMOST, x, y, NULL, NULL, SWP_NOSIZE);
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
	_winHandle = CreateWindow(_winClassName, (TCHAR*)_winTitle.c_str(),	WS_CAPTION |WS_SYSMENU |WS_MINIMIZEBOX|WS_MAXIMIZEBOX , CW_USEDEFAULT, 0, winRect.right, winRect.bottom, NULL, NULL, instance, NULL);

	if (!_winHandle)
		return FALSE;

	_glContext.init(_winHandle);
	
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
		close();
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
