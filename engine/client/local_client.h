#pragma once

#include "input/input.h"

#include "server/server_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LocalClient : public Updatable {
public:
	static const uint FRAMERATE = 60;

public:
	virtual ~LocalClient() {}

public:
	// interface: Updatable
	virtual void update();

protected:
	virtual void handleControls(const InputData& controls, ServerRequests::Client& request) = 0;
	virtual void showWorld(const ServerState& fromArbiter, ServerState& toVideo) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
