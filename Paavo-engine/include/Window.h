#ifndef PAAVO_WINDOW_H
#define PAAVO_WINDOW_H

#define PAAVO_EXPORT __declspec(dllexport)
#define PAAVO_IMPORT __declspec(dllimport)

#include <string>
#include <Windows.h>
#include <tchar.h>

namespace pv {

	class PAAVO_EXPORT Window
	{
	public:
		Window();
		~Window();

		// Public methods.
		bool create(const std::wstring& title, int width, int height);
		bool update();


	private:
		// Private members needed for window creation.
		HWND _winHandle;
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
		virtual int _wndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

		// This method gets current windows handle and our stored pointer to its class and then routes
		// event handling to the objects own wndProc -method.
		static LRESULT CALLBACK _routeWndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
	};

} // namespace pv

#endif // PAAVO_WINDOW_H
