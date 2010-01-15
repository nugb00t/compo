#ifndef LOCAL_CLIENT_INTERFACE_INCLUDED
#define LOCAL_CLIENT_INTERFACE_INCLUDED

#include "input/input.h"

#include "server/server_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LocalClient : public Updatable {
public:
	static const unsigned FRAMERATE = 60;

public:
    LocalClient();
    virtual ~LocalClient() = 0;

public:
	// interface: Updatable
	virtual void update();

protected:
	virtual void handleControls(const InputData& controls, ServerRequests::Client& request) = 0;
	virtual void showWorld(const ServerState& fromArbiter, ServerState& toVideo) = 0;

private:
    InputPtr input_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
