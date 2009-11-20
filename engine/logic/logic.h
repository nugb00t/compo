#ifndef LOGIC_INCLUDED
#define LOGIC_INCLUDED

#include "logic_component.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Logic : public kaynine::Singleton<Logic> {
public:
	void decide(const ServerState& last, ServerRequests::Entity entities[ServerState::MAX_ENTITIES]);

	friend struct kaynine::Singleton<Logic>;

private:
    LogicComponentRegistry registry_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
