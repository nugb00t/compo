#ifndef SERVER_INCLUDED
#define SERVER_INCLUDED

#include "server_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Server : public kaynine::PulseThreadObject {
	static const unsigned PERIOD = 16;
	static const unsigned DELAY = 4 * 10;

    static const unsigned HISTORY_DEPTH = 4;

	typedef kaynine::CyclicBuffer<ServerState, HISTORY_DEPTH> States;

public:
	// interface: kaynine::PulseThreadObject
    virtual bool initialize();
    virtual bool update();
    virtual void terminate() {}
	virtual kaynine::Event& quit();
	virtual const unsigned period() const { return PERIOD; }	// *1 milliseconds
	virtual const unsigned delay() const { return DELAY; }		// *100 nanoseconds

private:
	States states_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
