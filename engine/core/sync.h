#ifndef SYNC_INCLUDED
#define SYNC_INCLUDED

#include "client/client_data.h"

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
    typedef kaynine::FrameBuffer<ClientData> ClientToArbiter;

public:
	LogicToVideo& logicToVideo() { return logicToVideoFB_; }
    ClientToArbiter& clientToArbiter() { return clientToArbiterFB_; }

private:
	LogicToVideo logicToVideoFB_;
    ClientToArbiter clientToArbiterFB_;

	friend struct kaynine::Singleton<Sync>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
