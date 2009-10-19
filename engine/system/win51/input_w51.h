#ifndef INPUT_W51_INCLUDED
#define INPUT_W51_INCLUDED

#include "system/input_interface.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class InputW51 : public InputInterface, public kaynine::Singleton<InputW51> {
public:
	InputW51();

	void handleRawInput(HRAWINPUT handle);

private:
	Controls controls_;

	friend struct kaynine::Singleton<InputW51>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
