#ifndef SERVER_INCLUDED
#define SERVER_INCLUDED

#include "server_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Server : public kaynine::ThreadBase {
    static const unsigned HISTORY_DEPTH = 4;

	typedef kaynine::CyclicBuffer<ServerState, HISTORY_DEPTH> States;

public:
    // interface: kaynine::ThreadBase
    virtual bool initialize();
    virtual bool update();
    virtual void terminate() {}

private:
	States states_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
