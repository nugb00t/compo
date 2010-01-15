#ifndef MESSAGE_SINK_W51_INCLUDED
#define MESSAGE_SINK_W51_INCLUDED

#include "system/system_loop.h"
#include "input/win51/input_w51.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MessageSinkW51 : public SystemLoop {
    static const unsigned PERIOD = 10;

public:
    // interface: kaynine::Threaded
    virtual bool initialize();
    virtual bool update();
    virtual void terminate() { if (window_) window_->destroy(); }

private:
    static LRESULT CALLBACK messageHandler(HWND, UINT, WPARAM, LPARAM);

private:
    InputW51 input_;

    kaynine::Timer timer_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
