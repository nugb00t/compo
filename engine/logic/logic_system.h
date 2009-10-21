#ifndef LOGIC_INTERFACE_INCLUDED
#define LOGIC_INTERFACE_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Logic : public Callable, public Updatable, public kaynine::Singleton<Logic> {
	static const unsigned FRAMERATE = 20;

public:
	// interface: Callable
	virtual void operator()();

	// interface: Updatable
	void update(const unsigned msec);

	friend struct kaynine::Singleton<Logic>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
