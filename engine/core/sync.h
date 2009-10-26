#ifndef SYNC_INCLUDED
#define SYNC_INCLUDED

#include "system/input_interface.h"
#include "client/local_client_interface.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const TCHAR EXIT_SIGNAL_NAME[] = _T("COMPONENTS_EXIT_SIGNAL");

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Sync : public kaynine::Singleton<Sync> {
public:
	static const unsigned MAX_ENTITIES = 4096;
    static const unsigned MAX_CLIENTS = 4;

public:
	struct Entities {
		Entity::Params entities[MAX_ENTITIES];
		unsigned long age;
	};

	typedef kaynine::FrameBuffer<Entities> LogicToVideo;
    typedef kaynine::FrameBuffer<InputInterface::Controls> InputToClient;
    typedef kaynine::FrameBuffer<LocalClientInterface::Delta> ClientToArbiter;

public:
	LogicToVideo& logicToVideo() { return logicToVideoFB_; }
	InputToClient& inputToClient() { return inputToClientFB_; }
    ClientToArbiter& clientToArbiter() { return clientsToArbiterFB_; }

private:
	LogicToVideo logicToVideoFB_;
	InputToClient inputToClientFB_;
    ClientToArbiter clientsToArbiterFB_;

	friend struct kaynine::Singleton<Sync>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
