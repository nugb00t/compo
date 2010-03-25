#pragma once

#ifdef PLATFORM_WIN51
#include "system/system_loop.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SystemLoopW51 : public SystemLoop {
    static const uint PERIOD = 5;

public:
    // interface: kaynine::ThreadObject
    virtual bool initialize();
    virtual bool update();
    virtual void terminate();

private:
    static LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);

private:
    kaynine::Timer timer_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
