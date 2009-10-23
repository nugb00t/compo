#ifndef SYNC_INCLUDED
#define SYNC_INCLUDED

#include "system/input_interface.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const TCHAR EXIT_SIGNAL_NAME[] = _T("COMPONENTS_EXIT_SIGNAL");

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Sync : public kaynine::Singleton<Sync> {
public:
	static const unsigned MAX_ENTITIES = 4096;

public:
	struct Entities {
		Entity::Params entities[MAX_ENTITIES];
		unsigned long age;
	};

	typedef kaynine::FrameBuffer<Entities>		LogicToVideo;
	typedef kaynine::FrameBuffer<InputInterface::Controls>		InputToClient;

public:
	LogicToVideo& logicToVideo() { return logicToVideoFB_; }
	InputToClient& inputToClient() { return inputToClientFB_; }

private:
	LogicToVideo logicToVideoFB_;
	InputToClient inputToClientFB_;

	friend struct kaynine::Singleton<Sync>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
