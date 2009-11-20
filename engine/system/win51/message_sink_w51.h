#ifndef MESSAGE_SINK_W51_INCLUDED
#define MESSAGE_SINK_W51_INCLUDED

#include "window/win51/window_w51.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MessageSinkW51 {
public:
    struct Params {
        kaynine::Event& signal;
        const unsigned period;

        Params(kaynine::Event& signal_, const unsigned period_) : signal(signal_), period(period_) {}
        Params(const Params& other) : signal(other.signal), period(other.period) {}
    };

public:
    static DWORD WINAPI threadFunc(void* something);

private:
    static LRESULT CALLBACK messageHandler(HWND, UINT, WPARAM, LPARAM);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
