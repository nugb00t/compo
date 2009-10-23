#include "stdafx.h"

#ifdef PLATFORM_WIN51
#include "message_sink_w51.h"

#include "core/sync.h"
#include "core/time.h"

#include "input_w51.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MessageSinkW51::operator()() {
	window_ = new WindowW51(&MessageSinkW51::messageHandler);
	CHECKED_CALL(window_->create(800, 600, 32, 0, false));

	InputW51::inst();

	kaynine::Event exitSignal(EXIT_SIGNAL_NAME);
	MSG	msg;

	while (!exitSignal.isSet())
		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			if (msg.message == WM_QUIT) {
				exitSignal.set();
			} else {
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}

	window_->destroy();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK MessageSinkW51::messageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
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

		case WM_INPUT:
			InputW51::inst().processRawInput(reinterpret_cast<HRAWINPUT>(lParam), Time::inst().msec());
			break;

		case WM_SYSCOMMAND:
			if (wParam == SC_SCREENSAVE || wParam == SC_MONITORPOWER)
				return 0;
			else
				break;
	}

	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
