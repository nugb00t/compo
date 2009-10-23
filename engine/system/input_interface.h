#ifndef INPUT_INTERFACE_INCLUDED
#define INPUT_INTERFACE_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Input system that tracks the time of the input event in addition to the event itself.
// May allow for more precise (?) button handling and / or smarter (?) axis interpolation.
class InputInterface {
public:
	static const unsigned FRAMERATE = 60;

    static const unsigned BUTTON_COUNT = 256;      // windows VKeys
    static const unsigned AXIS_HISTORY = 4;

    // buttons
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
        unsigned time;
        int value;
    };

    struct AxisEventHistory {
        static const unsigned DEPTH = 4;

        AxisEvent events[DEPTH];

        void add(const unsigned time, const int value);
    };

    // the whole struct
    struct Controls {
        ButtonInfo buttons[BUTTON_COUNT];
        AxisEventHistory axis[AXIS_COUNT];
		unsigned long age;
    };

public:
    InputInterface();

    const Controls& controls() const { return controls_; }

protected:
    Controls controls_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef kaynine::Holder<InputInterface> Input;

}

#endif
