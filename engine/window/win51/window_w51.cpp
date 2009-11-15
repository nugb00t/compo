#include "stdafx.h"

#ifdef PLATFORM_WIN51
#include "window_w51.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const TCHAR	WindowW51::CLASS_NAME[]	= _T("Components window");
const TCHAR	WindowW51::WND_TITLE[]	= _T("Components");

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WindowW51::WindowW51(WNDPROC messageHandler)
:	messageHandler_(messageHandler),
    window_(0),
	context_(0),
	format_(0),
	width_(0),
	height_(0),
	fullscreen_(false)
{}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WindowW51::~WindowW51() {
	destroy();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool WindowW51::boolean_test() const {
	return window_ && context_ && format_ && width_ && height_;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool WindowW51::choosePixelFormat(BYTE colorBits, BYTE alphaBits, BYTE depthBits, BYTE stencilBits) {
	PIXELFORMATDESCRIPTOR pfd;

	::ZeroMemory (&pfd, sizeof(pfd));
	pfd.nSize			= sizeof(pfd);
	pfd.nVersion		= 1;
	pfd.dwFlags			= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.cColorBits		= colorBits;
	pfd.cAlphaBits		= alphaBits;
	pfd.cDepthBits		= depthBits;
	pfd.cStencilBits	= stencilBits;
	pfd.cAccumBits		= 32;
	pfd.iPixelType		= PFD_TYPE_RGBA;
	pfd.iLayerType		= PFD_MAIN_PLANE;

	format_ = ::ChoosePixelFormat(context_, &pfd);

	return format_ && ::SetPixelFormat(context_, format_, &pfd);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool WindowW51::create(const unsigned width, 
							 const unsigned height, 
							 const unsigned colorBits, 
							 const unsigned frequency, 
							 const bool fullscreen)
{
	WNDCLASS wc;
	wc.style			= CS_OWNDC;
	wc.lpfnWndProc		= messageHandler_;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= GetModuleHandle(NULL);
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= CLASS_NAME;

	if (!::RegisterClass(&wc)) {
		::MessageBox(NULL, _T("Failed To Register The WindowInterface Class."), _T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	DEVMODE devMode;
	// adjust for fullscreen
	fullscreen_ = fullscreen;
	if (fullscreen_) {
		memset(&devMode, 0, sizeof(devMode));

		devMode.dmSize				= sizeof(devMode);
		devMode.dmPelsWidth			= width;
		devMode.dmPelsHeight		= height;
		devMode.dmBitsPerPel		= colorBits;
		devMode.dmDisplayFrequency	= frequency;
		devMode.dmFields			= DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

		if (::ChangeDisplaySettings(&devMode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			fullscreen_ = false;
	}

	// adjust screen size
	DWORD exStyle;
	DWORD style;

	RECT rc;
	rc.left		= 0;
	rc.top		= 0;
	rc.right	= width_	= width;
	rc.bottom	= height_	= height;

	if (fullscreen_) {
		exStyle	= WS_EX_APPWINDOW;
		style	= WS_POPUP;
	} else {
		::memset(&devMode, 0, sizeof(devMode));
		devMode.dmSize = sizeof(devMode);
		::EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode);

		::OffsetRect(&rc, devMode.dmPelsWidth / 4, devMode.dmPelsHeight / 4);

		exStyle	= WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		style	= WS_OVERLAPPEDWINDOW;
	}
	::AdjustWindowRectEx(&rc, style, false, exStyle);

	window_ = ::CreateWindowEx(exStyle,
							 CLASS_NAME,
							 WND_TITLE,
							 style | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
							 rc.left, 
							 rc.top, 
							 rc.right - rc.left, 
							 rc.bottom - rc.top,
							 0,
							 0, 
							 wc.hInstance, 
							 0);
	if (!window_) {
		destroy();
		::MessageBox(NULL, _T("WindowInterface Creation Error."), _T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	::ShowWindow(window_, SW_SHOW);
	::SetForegroundWindow(window_);
	::SetFocus(window_);
	//::ShowCursor(FALSE);

	context_ = ::GetDC(window_);
	return context_ != 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WindowW51::destroy() {
	::ShowCursor(TRUE);

	if (fullscreen_) {
		::ChangeDisplaySettings(NULL, 0);
		::ShowCursor(TRUE);
		fullscreen_ = false;
	}

	if (context_) {
		::ReleaseDC(window_, context_);
		context_ = NULL;
	}

	format_ = 0;

	if (window_) {
		::DestroyWindow(window_);
		window_ = NULL;
	}

	::UnregisterClass(CLASS_NAME, ::GetModuleHandle(NULL));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif