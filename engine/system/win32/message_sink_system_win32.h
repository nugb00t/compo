#ifndef MESSAGE_SINK_SYSTEM_W32_INCLUDED
#define MESSAGE_SINK_SYSTEM_W32_INCLUDED

#include "system/message_sink_system.h"
#include "system/window_system.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MessageSinkSystemW32 : public MessageSinkSystem {
public:
    MessageSinkSystemW32();

	void operator()();

private:
    static LRESULT CALLBACK messageHandler(HWND, UINT, WPARAM, LPARAM);

    void loop();

private:
    WindowSystemPtr window_;

    Controls controls_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
