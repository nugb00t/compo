#pragma once

#include "window/window.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WindowW51 : public Window, public kaynine::IntrusivePtrBase {
	static const TCHAR	CLASS_NAME[];
	static const TCHAR	WND_TITLE[];

public:
	WindowW51();
	virtual ~WindowW51();

	// interface: safe_bool
	virtual bool boolean_test() const;

	// interface: Window
	virtual bool create(const WNDPROC wndProc,
						const uint width,
						const uint height, 
						const uint colorBits, 
						const uint frequency, 
						const bool fullscreen = true);

	virtual bool choosePixelFormat(BYTE colorBits, BYTE alphaBits, BYTE depthBits, BYTE stencilBits);

	virtual void destroy();

	virtual HWND handle() const { return window_;}

	virtual HDC context() const { return context_; }

	virtual int format() const { return format_; }

	virtual void swapBuffers() { ::SwapBuffers(context_); }

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
