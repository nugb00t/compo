#ifndef INPUT_INTERFACE_INCLUDED
#define INPUT_INTERFACE_INCLUDED

#include "input/input_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef kaynine::Holder<class InputInterface> Input;

class InputInterface {
public:
	static const unsigned FRAMERATE = 60;

public:
	InputInterface()  { Input::set(*this); }

    const InputData& controls() const { return controls_; }

protected:
    InputData controls_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
