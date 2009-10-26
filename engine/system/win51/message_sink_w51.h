#ifndef MESSAGE_SINK_W51_INCLUDED
#define MESSAGE_SINK_W51_INCLUDED

#include "system/message_sink_interface.h"

#include "window/win51/window_w51.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MessageSinkW51 : public MessageSinkInterface {
public:
	void operator()();

private:
    static LRESULT CALLBACK messageHandler(HWND, UINT, WPARAM, LPARAM);

private:
    WindowW51Ptr window_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
