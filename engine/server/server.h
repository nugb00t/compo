#ifndef SERVER_INCLUDED
#define SERVER_INCLUDED

#include "server/server_view.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Server : public Callable, public kaynine::Singleton<Server> {
	static const unsigned FRAMERATE = 10;
    static const unsigned HISTORY_DEPTH = 4;

public:
	// interface: Callable
	virtual void operator()();

private:
    kaynine::CyclicBuffer<ServerView, HISTORY_DEPTH> states_;

	friend struct kaynine::Singleton<Server>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
