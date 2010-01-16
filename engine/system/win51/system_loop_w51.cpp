#include "stdafx.h"

#ifdef PLATFORM_WIN51
#include "system_loop_w51.h"

#include "engine.h"
#include "game.h"

#include "input/win51/input_w51.h"

#include "core/profiler.h"
#include "core/sync.h"
#include "core/time.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SystemLoopW51::initialize() {
    if (!g_engine.window->create(SystemLoopW51::wndProc, 800, 600, 32, 0, false))
        return false;

    // this needs a proper sync
    assert(g_engine.window->handle());
    timer_.set(PERIOD, g_engine.window->handle());

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SystemLoopW51::update() {
    Profiler::StopWatch stopWatch(Profiler::SYSTEM);

    MSG	msg;
    while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        if (msg.message == WM_QUIT)
            return false;
        else {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SystemLoopW51::terminate() {
	if (g_engine.window) 
		g_engine.window->destroy(); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK SystemLoopW51::wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
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
			g_game.localClient->update();
			break;

		case WM_INPUT: // 0x00FF
			g_engine.inputW51->processRawInput(reinterpret_cast<HRAWINPUT>(lParam), Time::inst().msec());
			break;
	}

	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
