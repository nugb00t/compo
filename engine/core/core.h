#ifndef CORE_INCLUDED
#define CORE_INCLUDED

#include "utility/callable.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Core : public kaynine::Singleton<Core> {
public:
	Core();

	void clear()				{	systems_.clear();				}
	void add(Callable& system)	{	systems_.push_back(&system);	}
	void run();

	time_t time() const;

private:
	boost::thread_group threads_;
	std::list<Callable*> systems_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif