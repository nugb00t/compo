#ifndef WINDOW_INTERFACE_INCLUDED
#define WINDOW_INTERFACE_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WindowInterface
{
public:
	WindowInterface();

	// own: WindowInterface
	virtual bool create(
		const unsigned width, 
		const unsigned height, 
		const unsigned colorBits, 
		const unsigned frequency, 
		const bool fullscreen) = 0;

	virtual bool choosePixelFormat(BYTE colorBits, BYTE alphaBits, BYTE depthBits, BYTE stencilBits) = 0;

	virtual void destroy() = 0;

	virtual HWND handle() const = 0;

	virtual HDC context() const = 0;

	virtual int format() const = 0;

	//virtual const unsigned width() const = 0;
	//virtual const unsigned height() const = 0;

	virtual void swapBuffers() = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Holder<WindowInterface> Window;

}

#endif
