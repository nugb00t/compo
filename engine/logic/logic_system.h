#ifndef LOGIC_INCLUDED
#define LOGIC_INCLUDED

#include "utility/callable.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Logic : public Callable, public kaynine::Singleton<Logic> {
public:
	// interface: Callable
	virtual void operator()();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
