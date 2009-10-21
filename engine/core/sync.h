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

	typedef kaynine::ReadableAccess<Entities>		LogicToVideoReadable;
	typedef kaynine::WritableAccess<Entities>		LogicToVideoWritable;
	typedef kaynine::FrameBufferAccess<Entities>	LogicToVideoAccess;

	typedef kaynine::ReadableAccess<InputInterface::Controls>		InputToClientReadable;
	typedef kaynine::WritableAccess<InputInterface::Controls>		InputToClientWritable;
	typedef kaynine::FrameBufferAccess<InputInterface::Controls>	InputToClientAccess;

public:
	LogicToVideoAccess& logicToVideo() { return logicToVideoFB_; }
	InputToClientAccess& inputToClient() { return inputToClientFB_; }

private:
	LogicToVideoAccess logicToVideoFB_;
	InputToClientAccess inputToClientFB_;

	friend struct kaynine::Singleton<Sync>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
