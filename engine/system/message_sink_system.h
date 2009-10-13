#ifndef MESSAGE_SINK_SYSTEM_INCLUDED
#define MESSAGE_SINK_SYSTEM_INCLUDED

#include "utility/holder.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Input system that tracks the time of the input event in addition to the event itself.
// May allow for more precise (?) button handling and / or smarter (?) axis interpolation.
class MessageSinkSystem : public Callable {
public:
    // buttons
    static const unsigned BUTTON_COUNT = 256;      // windows VKeys

    struct ButtonInfo {
        unsigned long pushed;
        unsigned long released;
    };

    // axis
    enum Axis {
        MOUSE_X,
        MOUSE_Y,
        MOUSE_WHEEL,

        AXIS_COUNT
    };

    struct AxisEvent {
        unsigned long time;
        int value;
    private:
        int padding;
    };

    struct AxisEventHistory {
        static const unsigned DEPTH = 4;

        AxisEvent axisEvents[DEPTH];
    };

    struct Controls {
        ButtonInfo buttons[BUTTON_COUNT];
        AxisEventHistory axis[AXIS_COUNT];
		unsigned long age;
    };

public:
	MessageSinkSystem();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Holder<MessageSinkSystem> MessageSink;

}

#endif
