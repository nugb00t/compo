#ifndef WINDOW_SYSTEM_W32_INCLUDED
#define WINDOW_SYSTEM_W32_INCLUDED

#include "window/window_system.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WindowSystemW32 : public WindowSystem {
	static const TCHAR	CLASS_NAME[];
	static const TCHAR	WND_TITLE[];

public:
	WindowSystemW32();
	virtual ~WindowSystemW32();

	// interface: safe_bool
	virtual bool boolean_test() const;

	// interface: Updatable
	virtual bool update(const float dt);

	// interface: WindowSystem
	virtual bool create(const unsigned width, const unsigned height);

	virtual bool create(
		const unsigned width, 
		const unsigned height, 
		const unsigned colorBits, 
		const unsigned frequency, 
		const bool fullscreen);

	virtual bool choosePixelFormat(BYTE colorBits, BYTE alphaBits, BYTE depthBits, BYTE stencilBits);

	virtual void destroy();

	virtual HWND handle() const { return window_;}

	virtual HDC context() const { return context_; }

	virtual int format() const { return format_; }

	virtual void swapBuffers() { ::SwapBuffers(context_); }


private:
	static LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);


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

#endif
