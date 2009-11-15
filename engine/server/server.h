#ifndef SERVER_INCLUDED
#define SERVER_INCLUDED

#include "server/server_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Server : public Callable, public kaynine::Singleton<Server> {
	static const unsigned FRAMERATE = 10;
    static const unsigned HISTORY_DEPTH = 4;

	typedef kaynine::CyclicBuffer<ServerState, HISTORY_DEPTH> States;

public:
	// interface: Callable
	virtual void operator()();

protected:
	void spawn();

private:
	States states_;

	friend struct kaynine::Singleton<Server>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
