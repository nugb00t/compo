#pragma once

#include "../window.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WindowW51 : public Window {
	static const TCHAR	CLASS_NAME[];
	static const TCHAR	WND_TITLE[];

public:
	WindowW51();
	virtual ~WindowW51();

	// interface: own
	virtual bool create(const WNDPROC wndProc,
						const uint width,
						const uint height, 
						const uint colorBits, 
						const uint frequency, 
						const bool fullscreen = true);

	virtual bool choosePixelFormat(BYTE colorBits, BYTE alphaBits, BYTE depthBits, BYTE stencilBits);

	virtual void destroy();

	virtual HDC context() const { return context_; }	// TODO: close?

	virtual int format() const { return format_; }		// TODO: close?

	virtual void swapBuffers() { ::SwapBuffers(context_); }

	// interface: Window
	virtual HWND handle() const { return window_;}

private:
	HWND		window_;
	HDC			context_;
	int			format_;

	int			width_;	
	int			height_;	
	bool		fullscreen_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
