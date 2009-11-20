#ifndef ARBITER_INTERFACE_INCLUDED
#define ARBITER_INTERFACE_INCLUDED

#include "server/server_data.h"

namespace engine {

typedef kaynine::Holder<class ArbiterInterface> Arbiter;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ArbiterInterface {
public:
    ArbiterInterface() { Arbiter::set(*this); }

	// interface: Own
    virtual void marshall(const ServerState& last, const ServerRequests& requests, ServerState& next) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
