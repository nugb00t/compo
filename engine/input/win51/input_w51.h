#ifndef INPUT_W51_INCLUDED
#define INPUT_W51_INCLUDED

#ifdef PLATFORM_WIN51
#include "input/input.h"

//#define USE_BUFFERED_RAW_INPUT

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class InputW51 : public Input {
#ifdef USE_BUFFERED_RAW_INPUT
	static const unsigned RAW_INPUT_BUFFER_COUNT = 16;
#endif

public:
	InputW51();

	inline void processRawInput(const HRAWINPUT handle, const unsigned now) {
#ifdef USE_BUFFERED_RAW_INPUT
		unbuffered(handle, now);
#else
		unbuffered(handle, now);
#endif
	}

private:
#ifdef USE_BUFFERED_RAW_INPUT
	void buffered(const HRAWINPUT handle, const unsigned now);
#endif
	void unbuffered(const HRAWINPUT handle, const unsigned now);

	void process(const RAWINPUT& raw, const unsigned now);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
#endif
