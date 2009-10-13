#ifndef INPUT_SYSTEM_INCLUDED
#define INPUT_SYSTEM_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Input system that tracks the time of the input event in addition to the event itself.
// May allow for more precise (?) button handling and / or smarter (?) axis interpolation.
class Input : public Updatable, public kaynine::Singleton<Input> {
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

        AxisEvent[DEPTH];
    };

    struct Controls {
        ButtonInfo buttons[BUTTON_COUNT];
        AxisEventHistory axis[AXIS_COUNT];
    };

public:
    // interface: Updatable
    void update(const float dt);

    // own
    const Controls& controls() const { return controls_; }

private:
    Controls controls_;

    friend struct kaynine::Singleton<Input>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
