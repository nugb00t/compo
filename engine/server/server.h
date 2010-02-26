#pragma once

#include "server_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Server : public kaynine::PulseThreadObject {
	static const uint PERIOD = 16;
	static const uint DELAY = 4 * 10;

    static const uint HISTORY_DEPTH = 4;

	typedef kaynine::CyclicBuffer<ServerState, HISTORY_DEPTH> States;

public:
	// interface: kaynine::PulseThreadObject
    virtual bool initialize();
    virtual bool update();
	virtual kaynine::Event& quit();
	virtual const uint period() const { return PERIOD; }	// *1 milliseconds
	virtual const uint delay() const { return DELAY; }		// *100 nanoseconds

private:
	States states_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
