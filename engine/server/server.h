#ifndef SERVER_INCLUDED
#define SERVER_INCLUDED

#include "server/server_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Server : public kaynine::Singleton<Server> {
    static const unsigned HISTORY_DEPTH = 4;

	typedef kaynine::CyclicBuffer<ServerState, HISTORY_DEPTH> States;

public:
    // kaynine::thread meta-interface
    bool initialize();
    bool update();
    void terminate() {}

protected:
	void spawn();

private:
	States states_;

	friend struct kaynine::Singleton<Server>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
