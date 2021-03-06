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
	_fullscreen = false;
	_inputVector = new std::vector < KEYBOARD >;
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

void Window::draw(std::vector<float>& vertices, std::vector<unsigned int>& elements)
{
	_glContext.render(vertices, elements);
}

void Window::setTitle(std::string title)
{
	_winTitle = std::wstring(title.begin(), title.end());
	SetWindowText(_winHandle, _winTitle.c_str());
}

bool Window::setSize(int width, int height) //TODO: Grafiikkakontekstin muutos ku ikkunan koko muuttuu
{
	_winWidth = width;
	_winHeight = height;

	_winRect.left = 0;
	_winRect.top = 0;
	_winRect.right = _winWidth;
	_winRect.bottom = _winHeight;

	AdjustWindowRect(&_winRect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, FALSE);

	SetWindowPos(_winHandle, HWND_TOPMOST, NULL, NULL, (_winRect.right - _winRect.left), (_winRect.bottom - _winRect.top), SWP_NOMOVE);

	//_glContext.clean();
	//_glContext.init(_winHandle);
	//_glContext.debug_resetContext();


	return true;
}

void Window::close()
{
	_glContext.clean();
	PostQuitMessage(0);
}

void Window::use(std::string shader)
{
	_glContext.use(shader);
}

void Window::setPosition(int x, int y)
{
	SetWindowPos(_winHandle, HWND_TOPMOST, x, y, NULL, NULL, SWP_NOSIZE);
}

GLuint Window::getShader(std::string shadername)
{
	if (shadername == "colorshader")
	return _glContext.getDefaultColorShader();

	if (shadername == "textureshader")
		return _glContext.getDefaultTextureShader();
}

// Private methods

BOOL Window::createWindow()
{
	_winInstance = GetModuleHandle(nullptr);
	registerClass(_winInstance);
	return initInstance(_winInstance, 1);
}

bool Window::setFullscreen(bool fullscreen) //TODO: Grafiikkakontekstin muutos ku ikkunan koko muuttuu
{

	if (!_fullscreen)
	{
		if (fullscreen)
		{
			_savedWindowClass = _wcex;
			_savedWindowClass.style = GetWindowLong(_winHandle, GWL_STYLE);
			GetWindowRect(_winHandle, &_winRect);
		}
		else return false;

		SetWindowLong(_winHandle, GWL_STYLE,
			_savedWindowClass.style &~(WS_CAPTION | WS_THICKFRAME));
		SetWindowLong(_winHandle, GWL_EXSTYLE,
			_savedWindowClass.style &~(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_STATICEDGE));


		MONITORINFO monitorInfo;
		monitorInfo.cbSize = sizeof(monitorInfo);
		GetMonitorInfo(MonitorFromWindow(_winHandle, MONITOR_DEFAULTTONEAREST), &monitorInfo);
		RECT monitor = monitorInfo.rcMonitor;
		SetWindowPos(_winHandle, HWND_TOPMOST, monitor.left, monitor.top, monitor.right-monitor.left, monitor.bottom-monitor.top, SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED); 

		//TODO:Tähän assertioita tai debugshittiä plssss koska SetWindowPos ei välttis onnistu
	}


	if (_fullscreen)
	{
		if (!fullscreen)
		{
			SetWindowLong(_winHandle, GWL_STYLE, _savedWindowClass.style);
			//SetWindowLong(_winHandle, GWL_EXSTYLE, _savedWindowClass.style); // ei välttis pakollinen missään määrin
			RECT newMonitor = _winRect; //ei kanssi gettaa suoraan _winRectiä missään yhteydessä
			
			SetWindowPos(_winHandle, NULL, _winRect.left, _winRect.top, (_winRect.right - _winRect.left), (_winRect.bottom - _winRect.top), SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);

		}
		else return false;

	}
	
	_fullscreen = fullscreen;
}

ATOM Window::registerClass(HINSTANCE _instance)
{
	_wcex.cbSize = sizeof(WNDCLASSEX);

	_wcex.style = CS_HREDRAW | CS_VREDRAW;
	_wcex.lpfnWndProc = &Window::routeWndProc;
	_wcex.cbClsExtra = 0;
	_wcex.cbWndExtra = 0;
	_wcex.hInstance = _instance;
	_wcex.hIcon = NULL;	// LoadIcon(_instance, IDI_ERROR);
	_wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	_wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	_wcex.lpszMenuName = NULL;
	_wcex.lpszClassName = _winClassName;
	_wcex.hIconSm = NULL;	//LoadIcon(_wcex.hInstance, IDI_ASTERISK);

	return RegisterClassEx(&_wcex);
}

BOOL Window::initInstance(HINSTANCE instance, int cmdShow)
{

	RECT winRect;
	winRect.left = 0;
	winRect.top = 0;
	winRect.right = _winWidth;
	winRect.bottom = _winHeight;
	AdjustWindowRect(&winRect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, FALSE);

	_winHandle = CreateWindow(_winClassName, (TCHAR*)_winTitle.c_str(), WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, (winRect.right - winRect.left), (winRect.bottom - winRect.top), NULL, NULL, instance, NULL);

	if (!_winHandle)
		return FALSE;

	_glContext.init(_winHandle);
	
	SetWindowLongPtr(_winHandle, GWLP_USERDATA, (long)this);
	ShowWindow(_winHandle, cmdShow);
	UpdateWindow(_winHandle);
	
	return TRUE;
}

bool Window::isKeyDown(KEYBOARD key)
{	
	if (_inputVector->size() > 0)
	{
		std::vector<KEYBOARD>::iterator it = _inputVector->begin();

		while (it != _inputVector->end())
		{
			if ((*it) == key)
				return true;
			it++;
		}
	}
	return false;
}

void Window::addInput(WPARAM wparam)
{
	KEYBOARD key = toKey(wparam);

	_inputVector->push_back(key);
	
}

void Window::removeInput(WPARAM wparam)
{
	if (_inputVector->size() > 0)
	{
		std::vector<KEYBOARD>::iterator it = _inputVector->begin();
		KEYBOARD key = toKey(wparam);

		while (it != _inputVector->end())
		{
			if ((*it) == key)
				it = _inputVector->erase(it);
			else
				it++;
		}
	}
}

KEYBOARD Window::toKey(WPARAM wparam)
{
	if (wparam == VK_DOWN)
		return KEYBOARD::DOWN;

	if (wparam == VK_UP)
		return KEYBOARD::UP;

	if (wparam == VK_RIGHT)
		return KEYBOARD::RIGHT;

	if (wparam == VK_LEFT)
		return KEYBOARD::LEFT;
	if (wparam == VK_SPACE)
		return KEYBOARD::SPACE;

	if (wparam == W_KEY)
		return KEYBOARD::W;

	if (wparam == A_KEY)
		return KEYBOARD::A;

	if (wparam == S_KEY)
		return KEYBOARD::S;

	if (wparam == D_KEY)
		return KEYBOARD::D;

	if (wparam == VK_ESCAPE)
		return KEYBOARD::ESC;

	if (wparam == VK_RETURN)
		return KEYBOARD::ENTER;
	
}

int Window::wndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wparam);
		wmEvent = HIWORD(wparam);
		break;
	case WM_PAINT:
		_hdc = BeginPaint(window, &ps);
		EndPaint(window, &ps);
		break;

	case WM_DESTROY:
		close();
		break;

	case WM_KEYDOWN:
		addInput(wparam);
		break;

	case WM_KEYUP:
		removeInput(wparam);
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
