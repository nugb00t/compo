#ifndef CORE_INCLUDED
#define CORE_INCLUDED

#include "utility/callable.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Core : public kaynine::Singleton<Core> {
public:
	void clear()				{	systems_.clear();				}
	void add(Callable& system)	{	systems_.push_back(&system);	}
	void run();

private:
	boost::thread_group threads_;
	std::list<Callable*> systems_;

	friend struct kaynine::Singleton<Core>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
