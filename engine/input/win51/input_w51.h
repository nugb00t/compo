#ifndef INPUT_W51_INCLUDED
#define INPUT_W51_INCLUDED

#include "input/input_interface.h"

//#define USE_BUFFERED_RAW_INPUT

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class InputW51 : public InputInterface, public kaynine::Singleton<InputW51> {
#ifdef USE_BUFFERED_RAW_INPUT
	static const unsigned RAW_INPUT_BUFFER_COUNT = 16;
#endif

public:
	InputW51();

	inline void processRawInput(const HRAWINPUT handle, const unsigned long now) {
#ifdef USE_BUFFERED_RAW_INPUT
		unbuffered(handle, now);
#else
		unbuffered(handle, now);
#endif
	}

private:
#ifdef USE_BUFFERED_RAW_INPUT
	void buffered(const HRAWINPUT handle, const unsigned long now);
#endif
	void unbuffered(const HRAWINPUT handle, const unsigned long now);

	void process(const RAWINPUT& raw, const unsigned long now);

	friend struct kaynine::Singleton<InputW51>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
