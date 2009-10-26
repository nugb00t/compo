#include "stdafx.h"

#include "core.h"
#include "profiler.h"

#ifdef PLATFORM_WIN51
	#include "system/win51/message_sink_w51.h"
#endif

#ifdef VIDEO_DIRECT3D9
	#include "video/direct3d9/video_d3d9.h"
#endif

#include "server/server.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Core::create(Platform platform, Video video) {
    switch (platform) {
#ifdef PLATFORM_WIN51
        case Windows51:
            messageSink_ = new MessageSinkW51;
            break;
#endif
    }

    switch (video) {
#ifdef VIDEO_DIRECT3D9
        case Direct3D9:
            video_ = new VideoD3D9;
            break;
#endif
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Core::run() {
	Profiler::inst();

	// TODO: migrate to win32 threads?
    boost::thread_group threads;

    threads.create_thread(boost::ref(Server::inst()));
    threads.create_thread(boost::ref(*messageSink_));
    threads.create_thread(boost::ref(*video_));

	threads.join_all();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
