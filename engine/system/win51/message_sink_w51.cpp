#include "stdafx.h"

#ifdef PLATFORM_WIN51
#include "message_sink_w51.h"

#include "input/win51/input_w51.h"

#include "core/sync.h"
#include "core/time.h"
#include "client/local_client_interface.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MessageSinkW51::operator()() {
	window_ = new WindowW51(&MessageSinkW51::messageHandler);
	CHECKED_CALL(window_->create(800, 600, 32, 0, false));

	InputW51::inst();

	kaynine::Timer clientTimer(unsigned(1000.f / LocalClientInterface::FRAMERATE));

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
		//case WM_SIZE: // 0x0005
		//	pRenderLoop_->reshapeRenderer(LOWORD(lParam), HIWORD(lParam));
		//	break;

		//case WM_ACTIVATE: // 0x0006
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

		//case WM_SETFOCUS: // 0x0007
		//	setClipCursor(hWnd);
		//	KN_TRACE(_T(" [engine] focus window\n"));
		//	break;

		//case WM_KILLFOCUS: // 0x0008
		//	setClipCursor(hWnd, false);
		//	KN_TRACE(_T(" [engine] unfocus window\n"));
		//	break;

		case WM_CLOSE: // 0x0010
			::PostQuitMessage(0);
			return 0;

		case WM_ERASEBKGND: // 0x0014
			return 0; // disallow

		case WM_SYSCOMMAND: // 0x0112
			if (wParam == SC_SCREENSAVE || wParam == SC_MONITORPOWER)
				return 0;
			else
				break;

		case WM_TIMER: // 0x0113
			LocalClient::inst().update();
			break;

		case WM_INPUT: // 0x00FF
			InputW51::inst().processRawInput(reinterpret_cast<HRAWINPUT>(lParam), Time::inst().msec());
			break;
	}

	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
