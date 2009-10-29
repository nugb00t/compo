#ifndef ARBITER_INTERFACE_INCLUDED
#define ARBITER_INTERFACE_INCLUDED

#include "client/client_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef kaynine::Holder<class ArbiterInterface> Arbiter;

class ArbiterInterface : public Updatable {
public:
    ArbiterInterface() { Arbiter::set(*this); }

	// interface: Updatable
	virtual void update(const unsigned msec);

protected:
    // own
    virtual void marshall(const ClientData& fromClient) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
