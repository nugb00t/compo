#ifndef SERVER_INCLUDED
#define SERVER_INCLUDED

#include "logic/logic_component.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Server : public kaynine::Singleton<Server> {
    static const unsigned HISTORY_DEPTH = 4;

	typedef kaynine::CyclicBuffer<ServerState, HISTORY_DEPTH> States;

public:
    struct Params {
        LogicComponentRegistry* registry;

        Params(LogicComponentRegistry* registry_) : registry(registry_) {}
    };

public:
    // kaynine::thread meta-interface
    bool initialize(Params* params);
    bool update();
    void terminate() {}

protected:
	void spawn();

private:
	States states_;
    Params* params_;

	friend struct kaynine::Singleton<Server>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
