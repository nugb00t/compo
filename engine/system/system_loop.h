#ifndef SYSTEM_LOOP_INCLUDED
#define SYSTEM_LOOP_INCLUDED

#include "window/window_interface.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SystemLoop : public kaynine::Threaded {
public:
    SystemLoop(WindowInterface* window) : window_(window) {}

protected:
    WindowInterface* window_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
