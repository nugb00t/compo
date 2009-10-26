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

		void add(const unsigned time, const int value)  {
			for (unsigned i = DEPTH; i > 0; --i)
				events[i] = events[i - 1];

			events[0].time = time;
			events[0].value = value;
		}
	};

	// the whole struct
	ButtonInfo buttons[BUTTON_COUNT];
	AxisEventHistory axis[AXIS_COUNT];
	unsigned long age;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
