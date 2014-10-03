#pragma once

#include <string>
#include <Windows.h>
#include <tchar.h>

#include "defines.h"

#include "GLContext.h"

namespace pv {
	/**
	 * Class for creating and handling windows.
	 */
	enum WINDOW_STYLE
	{
		NORMAL,
		DRAGGABLE,
	};
	class PAAVO_EXPORT Window
	{
	public:
		/**
		 * Default constructor.
		 */
		Window();

		/**
		* Constructor overload to create and show window when initialized.
		* Warning: No indication if window creation is not successfull.
		*
		* @param	title	Window title
		* @param	width	Window width
		* @param	height	Window height
		*/
		Window(const std::string& title, int width, int height);

		/**
		* Destructor
		*/
		~Window();

		// Public methods.

		/**
		 * Create and show window.
		 * 
		 * @param	title	Window title
		 * @param	width	Window width
		 * @param	height	Window height
		 * @return	True if window creation is successfull
		 */
		bool create(const std::string& title, int width, int height);

		/**
		 * Update window events. Important to run every frame.
		 *
		 * @return	True if window is still open.
		 */
		bool update();

		/**
		 * Clear screen with color.
		 * Values from 0.0 to 1.0.
		 *
		 * @param	r	Red
		 * @param	g	Green
		 * @param	b	Blue
		 * @param	a	Alpha
		 */
		void clearColor(float r, float g, float b, float a);
		/**
		* Swap buffers.
		*/
		void swap();

		/**
		 * Draw whats in framebuffer.
		 */
		void draw();
		/**
		* Changes the title.
		*/
		void setTitle(std::string title);
		/**
		* Changes the window size.
		*/
		bool setSize(int width, int height);
		


	private:
		// Private members needed for window creation.
		HWND _winHandle;
		HINSTANCE _winInstance;
		std::wstring _winTitle;
		TCHAR* _winClassName;
		MSG _winMessage;
		std::wstring _title;
		GLContext _glContext;
		
		int _winStyle;
		int _winWidth;
		int _winHeight;

		// Private methods for window creation.
		BOOL createWindow();
		ATOM registerClass(HINSTANCE instance);
		BOOL initInstance(HINSTANCE instance, int cmdShow);
		virtual int wndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

		// This method gets current windows handle and our stored pointer to its class and then routes
		// event handling to the objects own wndProc -method.
		static LRESULT CALLBACK routeWndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

	};

} // namespace pv
