#pragma once

#include <string>
#include <Windows.h>
#include <tchar.h>

#include <vector>
#include <deque>
#include <list>
#include "defines.h"
#include "GLContext.h"

namespace pv {

	enum KEYBOARD
	{
		DOWN,
		UP,
		LEFT,
		RIGHT,
		W,
		A,
		S,
		D
	};

	/**
	 * Class for creating and handling windows.
	 */
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
		void draw(std::vector<float>& vertices, std::vector<unsigned int>& elements);
		/**
		* Changes the title.
		*/
		void setTitle(std::string title);
		/**
		* Changes the window size.
		*/
		bool setSize(int width, int height);
		/**
		* Closes the window.
		*/
		void close();

		/**
		* Sets the position of the window.
		*/
		void setPosition(int x, int y);

		bool setFullscreen(bool fullscreen);

		GLuint getShader();


		int giveInput(WPARAM wparam);
		//int getInput(std::deque <KEYBOARD> inputBuffer);

	private:
		// Private members needed for window creation.
		HWND _winHandle;
		HINSTANCE _winInstance;
		std::wstring _winTitle;
		TCHAR* _winClassName;
		MSG _winMessage;
		GLContext _glContext;
		HDC _hdc;
		WNDCLASSEX _wcex;
		RECT _winRect;
		WNDCLASSEX _savedWindowClass;
		int _winWidth;
		int _winHeight;
		bool _fullscreen;
		KEYBOARD getInput();

		// Private methods for window creation.
		BOOL createWindow();
		ATOM registerClass(HINSTANCE instance);
		BOOL initInstance(HINSTANCE instance, int cmdShow);
		virtual int wndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

		// This method gets current windows handle and our stored pointer to its class and then routes
		// event handling to the objects own wndProc -method.
		static LRESULT CALLBACK routeWndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

		KEYBOARD _lastInput;
		

	};

} // namespace pv
