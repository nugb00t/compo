#include "stdafx.h"

#ifdef PLATFORM_WIN32
#include "core/sync.h"

#include "message_sink_system_win32.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MessageSinkSystemW32::MessageSinkSystemW32() {
	//CHECKED_CALL(::RegisterRawInputDevices());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK MessageSinkSystemW32::messageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
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

void MessageSinkSystemW32::operator()() {
	MSG	msg;
	kaynine::Event exitSignal(EXIT_SIGNAL_NAME);

	while (!exitSignal.isSet())
		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			if (msg.message == WM_QUIT) {
				exitSignal.set();
			} else {
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
