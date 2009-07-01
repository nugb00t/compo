#include "stdafx.h"

#include "video/directx/video_system_dx.h"
#include "window/win32/window_system_w32.h"

#include "logic/logic_system.h"
#include "video/video_system.h"
#include "core/core.h"

#include "entities/orb/orb.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int __cdecl _tmain(int UNUSED(argc), _TCHAR* UNUSED(argv[])) {
	CHECKED_CALL(kaynine::setCurrentDirectory());

	engine::VideoSystemDX video;
	engine::WindowSystemW32 window;

	game::Orb orb;

	engine::Core::get().add(engine::Logic::get());
	engine::Core::get().add(engine::Video::get());
	engine::Core::get().run();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

