#ifndef TIMER_INCLUDED
#define TIMER_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Timer : public kaynine::Singleton<Timer> {
protected:
	Timer();

public:
	const unsigned long now() const;

	friend struct kaynine::Singleton<Timer>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
