#ifndef LOGIC_INCLUDED
#define LOGIC_INCLUDED

#include "logic_component.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Logic : public kaynine::Singleton<Logic> {
public:
    Logic() : registry_(NULL) {}

    void initialize(LogicComponentRegistry* registry) { assert(!registry_ && registry); registry_ = registry; }

	void decide(const ServerState& last, ServerRequests::Entity entities[ServerState::MAX_ENTITIES]);

private:
    LogicComponentRegistry* registry_;

    friend struct kaynine::Singleton<Logic>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
