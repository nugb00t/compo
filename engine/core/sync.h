#ifndef SYNC_INCLUDED
#define SYNC_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const TCHAR EXIT_SIGNAL_NAME[] = _T("COMPONENTS_EXIT_SIGNAL");

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Sync : public kaynine::Singleton<Sync> {
public:
	static const unsigned MAX_ENTITIES = 4096;

public:
	struct EntityParams {
		Vector3 position;
		Vector3 rotation;
	};

	struct LogicToVideo {
		EntityParams entityParams[MAX_ENTITIES];
		float age;
	};

	typedef kaynine::ReadableAccess<LogicToVideo>		LogicToVideoReadable;
	typedef kaynine::WritableAccess<LogicToVideo>		LogicToVideoWritable;
	typedef kaynine::FrameBufferAccess<LogicToVideo>	logicToVideoAccess;

public:
	logicToVideoAccess& logicToVideo()	{	return logicToVideoFB_;	}

private:
	logicToVideoAccess logicToVideoFB_;

	friend struct kaynine::Singleton<Sync>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
