#ifndef LOGIC_INCLUDED
#define LOGIC_INCLUDED

#include "utility/callable.h"
#include "utility/updatable.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Logic : public Callable, public Updatable, public kaynine::Singleton<Logic> {
	static const unsigned FRAMERATE = 20;

public:
	// interface: Callable
	virtual void operator()();

	// interface: Updatable
	void update(const float dt);

	friend struct kaynine::Singleton<Logic>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
