#ifndef WINDOW_W51_INCLUDED
#define WINDOW_W51_INCLUDED

#include "system/window_interface.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WindowW51 : public WindowInterface, public kaynine::IntrusivePtrBase {
	static const TCHAR	CLASS_NAME[];
	static const TCHAR	WND_TITLE[];

public:
	WindowW51(WNDPROC messageHandler);
	virtual ~WindowW51();

	// interface: safe_bool
	virtual bool boolean_test() const;

	// interface: WindowInterface
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
    WNDPROC     messageHandler_;
	HWND		window_;
	HDC			context_;
	int			format_;

	int			width_;	
	int			height_;	
	bool		fullscreen_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef boost::intrusive_ptr<WindowW51> WindowW51Ptr;

}

#endif
