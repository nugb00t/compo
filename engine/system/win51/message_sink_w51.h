#ifndef MESSAGE_SINK_W51_INCLUDED
#define MESSAGE_SINK_W51_INCLUDED

#include "system/message_sink_interface.h"
#include "system/window_interface.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MessageSinkW51 : public MessageSinkInterface {
public:
    MessageSinkW51();

	void operator()();

private:
    static LRESULT CALLBACK messageHandler(HWND, UINT, WPARAM, LPARAM);

    void loop();

private:
    WindowInterfacePtr window_;

    Controls controls_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
