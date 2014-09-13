#ifndef PAAVO_WINDOW_H
#define PAAVO_WINDOW_H

#define PAAVO_EXPORT __declspec(dllexport)
#define PAAVO_IMPORT __declspec(dllimport)

#include <string>
#include <Windows.h>
#include <tchar.h>

namespace pv {

	// anonymous namespace for window event handling
	// TODO: Try to get this function inside the class so each window has its own event handling method.
	namespace {
		LRESULT CALLBACK _wndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
	}

	class PAAVO_EXPORT Window
	{
	public:
		Window();
		~Window();

		// Public methods.
		bool create(const std::wstring& title, int width, int height);
		void update();
		bool isOpen();

	private:
		// Private members needed for window creation.
		HINSTANCE _winInstance;
		std::wstring _winTitle;
		TCHAR* _winClassName;
		MSG _winMessage;
		int _winWidth;
		int _winHeight;

		// Private methods for window creation.
		BOOL _createWindow();
		ATOM _registerClass(HINSTANCE instance);
		BOOL _initInstance(HINSTANCE instance, int cmdShow);

	};

} // namespace pv

#endif // PAAVO_WINDOW_H