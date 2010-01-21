#ifndef INPUT_DATA_INCLUDED
#define INPUT_DATA_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Track the time of the input event in addition to the event itself.
// May allow for more precise (?) button handling and / or smarter (?) axis interpolation.
struct InputData {
	static const unsigned BUTTON_COUNT = 256;      // windows VKeys
	static const unsigned AXIS_HISTORY = 4;

	// buttons
	struct ButtonInfo {
		unsigned pushed;
		unsigned released;
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

		AxisEvent(const unsigned time_, const int value_) 
			: time(time_), value(value_) {}

		AxisEvent() 
			: time(0), value(0) {}
	};

	// the whole struct
	ButtonInfo buttons[BUTTON_COUNT];
	kaynine::CyclicBuffer<AxisEvent, AXIS_HISTORY> axis[AXIS_COUNT];
	unsigned age;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
