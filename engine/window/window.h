#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Window
{
public:
	virtual bool create(
		const WNDPROC wndProc,
		const uint width, 
		const uint height, 
		const uint colorBits, 
		const uint frequency, 
		const bool fullscreen) = 0;

	virtual bool choosePixelFormat(BYTE colorBits, BYTE alphaBits, BYTE depthBits, BYTE stencilBits) = 0;

	virtual void destroy() = 0;

	virtual HWND handle() const = 0;

	virtual HDC context() const = 0;

	virtual int format() const = 0;

	//virtual const uint width() const = 0;
	//virtual const uint height() const = 0;

	virtual void swapBuffers() = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
