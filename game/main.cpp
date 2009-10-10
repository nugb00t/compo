#include "stdafx.h"

#include "video/directx/video_system_dx.h"
#include "window/win32/window_system_w32.h"

#include "logic/logic_system.h"
#include "video/video_system.h"
#include "core/core.h"

#include "playground/game_playground.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int __cdecl _tmain(int UNUSED(argc), _TCHAR* UNUSED(argv[])) {
	CHECKED_CALL(kaynine::setCurrentDirectory());

	engine::VideoSystemDX video;
	engine::WindowSystemW32 window;

	game_playground::Game game;

	engine::Core::inst().add(engine::Logic::inst());
	engine::Core::inst().add(engine::Video::inst());
	engine::Core::inst().run();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

