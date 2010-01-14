#ifndef MESSAGE_SINK_W51_INCLUDED
#define MESSAGE_SINK_W51_INCLUDED

#include "window/win51/window_w51.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MessageSinkW51 : public kaynine::Singleton<MessageSinkW51> {
public:
    struct Params {
        unsigned period;

        Params(const unsigned period_) : period(period_) {}
    };

private:
    MessageSinkW51() : params_(NULL) {}

public:
    // kaynine::thread meta-interface
    bool initialize(Params* params);
    bool update();
    void terminate() { if (window_) window_->destroy(); }

private:
    static LRESULT CALLBACK messageHandler(HWND, UINT, WPARAM, LPARAM);

private:
    Params* params_;
    WindowW51Ptr window_;
    kaynine::Timer timer_;

    friend struct kaynine::Singleton<MessageSinkW51>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
