#include "stdafx.h"

#include "window_system_w32.h"

#include "core/sync.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const TCHAR	WindowSystemW32::CLASS_NAME[]	= _T("ComponentsWND");
const TCHAR	WindowSystemW32::WND_TITLE[]	= _T("Components");

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WindowSystemW32::WindowSystemW32()
:	window_(0),
	context_(0),
	format_(0),
	width_(0),
	height_(0),
	fullscreen_(false)
{}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WindowSystemW32::~WindowSystemW32() {
	destroy();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool WindowSystemW32::boolean_test() const {
	return window_ && context_ && format_ && width_ && height_;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool WindowSystemW32::choosePixelFormat(BYTE colorBits, BYTE alphaBits, BYTE depthBits, BYTE stencilBits) {
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

bool WindowSystemW32::create(const unsigned width, const unsigned height) {
	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX), CS_CLASSDC, wndProc, 0L, 0L,
		::GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		CLASS_NAME, NULL};

	::RegisterClassEx(&wc);

	window_ = ::CreateWindow(CLASS_NAME, WND_TITLE,
		WS_OVERLAPPEDWINDOW, 100, 100, width_ = width, height_ = height,
		::GetDesktopWindow(), NULL, wc.hInstance, NULL);

	return window_ != 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool WindowSystemW32::create(const unsigned width, 
					const unsigned height, 
					const unsigned colorBits, 
					const unsigned frequency, 
					const bool fullscreen)
{
	WNDCLASS wc;
	wc.style			= /*CS_HREDRAW | CS_VREDRAW |*/ CS_OWNDC;
	wc.lpfnWndProc		= wndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= GetModuleHandle(NULL);
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= CLASS_NAME;

	if (!::RegisterClass(&wc)) {
		::MessageBox(NULL, _T("Failed To Register The WindowSystem Class."), _T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
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
		::MessageBox(NULL, _T("WindowSystem Creation Error."), _T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	::ShowWindow(window_, SW_SHOW);
	::SetForegroundWindow(window_);
	::SetFocus(window_);
	::ShowCursor(FALSE);

	context_ = ::GetDC(window_);
	return context_ != 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WindowSystemW32::destroy() {
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

void WindowSystemW32::update(const float UNUSED(dt)) {
	MSG	msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			kaynine::Event exitSignal(EXIT_SIGNAL_NAME);
			exitSignal.set();
		} else {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK WindowSystemW32::wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {

		// TODO: re-add activation event
		//case WM_ACTIVATE:
		//	if (LOWORD(wParam) && !HIWORD(wParam)) {		// activated && not minimized
		//		assert(pRenderLoop_);
		//		pRenderLoop_->syncObjects().evAppActive.set();
		//		KN_TRACE(_T(" [engine] activate window\n"));
		//	} else {
		//		assert(pRenderLoop_);
		//		pRenderLoop_->syncObjects().evAppActive.reset();
		//		KN_TRACE(_T(" [engine] deactivate window\n"));
		//	}
		//	break;

		case WM_CLOSE:
			::PostQuitMessage(0);
			return 0;

		case WM_ERASEBKGND:
			return 0;			// disallow

		// TODO: re-add cursor toggling
		//case WM_KILLFOCUS:
		//	setClipCursor(hWnd, false);
		//	KN_TRACE(_T(" [engine] unfocus window\n"));
		//	break;
		//case WM_SETFOCUS:
		//	setClipCursor(hWnd);
		//	KN_TRACE(_T(" [engine] focus window\n"));
		//	break;

		// TODO: re-add resizing
		//case WM_SIZE:
		//	pRenderLoop_->reshapeRenderer(LOWORD(lParam), HIWORD(lParam));
		//	break;

		case WM_SYSCOMMAND:
			if (wParam == SC_SCREENSAVE || wParam == SC_MONITORPOWER)
				return 0;
			else
				break;
	}

	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
