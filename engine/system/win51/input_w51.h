#ifndef INPUT_W51_INCLUDED
#define INPUT_W51_INCLUDED

#include "system/input_interface.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class InputW51 : public InputInterface, public kaynine::Singleton<InputW51> {
	//static const unsigned RAW_INPUT_BUFFER_COUNT = 16;

public:
	InputW51();

	inline void handleRawInput(const HRAWINPUT handle, const unsigned long now) { unbuffered(handle, now); }

private:
	//void buffered(const HRAWINPUT handle, const unsigned long now);
	void unbuffered(const HRAWINPUT handle, const unsigned long now);

	void process(const RAWINPUT& raw, const unsigned long now);

private:
	Controls controls_;

	friend struct kaynine::Singleton<InputW51>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
