#ifndef CORE_INCLUDED
#define CORE_INCLUDED

#include "system/message_sink_interface.h"
#include "video/video_interface.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Core : public kaynine::Singleton<Core> {
public:
    enum Platform {
#ifdef PLATFORM_WIN51
        Windows51,
#endif
        Platform_COUNT
    };

    enum Video {
#ifdef VIDEO_DIRECT3D9
        Direct3D9,
#endif
        Video_COUNT
    };

public:
    void create(Platform platform, Video video);
	void run();

private:
    MessageSinkPtr messageSink_;
    VideoPtr video_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
