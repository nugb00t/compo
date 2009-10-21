#ifndef INPUT_INTERFACE_INCLUDED
#define INPUT_INTERFACE_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Input system that tracks the time of the input event in addition to the event itself.
// May allow for more precise (?) button handling and / or smarter (?) axis interpolation.
class InputInterface {
public:
	static const unsigned FRAMERATE = 60;

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

        AxisEvent events[DEPTH];

		void add(const unsigned long time, const int value);
    };

    struct Controls {
        ButtonInfo buttons[BUTTON_COUNT];
        AxisEventHistory axis[AXIS_COUNT];
		unsigned long age;
    };
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
