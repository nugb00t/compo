#ifndef LOCAL_CLIENT_INTERFACE_INCLUDED
#define LOCAL_CLIENT_INTERFACE_INCLUDED

#include "input/input_data.h"
#include "server/server_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef kaynine::Holder<class LocalClientInterface> LocalClient;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LocalClientInterface : public Updatable {
public:
	static const unsigned FRAMERATE = 60;

public:
	LocalClientInterface() { LocalClient::set(*this); }

	// interface: Updatable
	virtual void update(const unsigned msec);

protected:
    // own
	virtual void handleControls(const InputData& controls, ServerRequests::Client& request) = 0;
	virtual void showWorld(const ServerState& fromArbiter, ServerState& toVideo) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
