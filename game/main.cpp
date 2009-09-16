#include "stdafx.h"

#include "video/directx/video_system_dx.h"
#include "window/win32/window_system_w32.h"

#include "logic/logic_system.h"
#include "video/video_system.h"
#include "core/core.h"

#include "entities/orb/orb.h"
#include "screens/profiler/profiler_screen.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int __cdecl _tmain(int UNUSED(argc), _TCHAR* UNUSED(argv[])) {
	CHECKED_CALL(kaynine::setCurrentDirectory());

	engine::VideoSystemDX video;
	engine::WindowSystemW32 window;

	game::Orb orb;
	//game::ProfilerScreen profilerScreen;

	engine::Core::inst().add(engine::Logic::inst());
	engine::Core::inst().add(engine::Video::inst());
	engine::Core::inst().run();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

