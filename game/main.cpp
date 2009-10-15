#include "stdafx.h"

#include "system/win32/message_sink_system_win32.h"
#include "video/directx/video_system_dx.h"

#include "logic/logic_system.h"
#include "video/video_system.h"
#include "core/core.h"

#include "playground/game_playground.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int __cdecl _tmain(int UNUSED(argc), _TCHAR* UNUSED(argv[])) {
	CHECKED_CALL(kaynine::setCurrentDirectory());

	// platform-specific subsystem instantiations
	MessageSinkSystemW32 messageSink;
	VideoSystemDX video;

	// the game
	game_playground::Game game;

	// threads
	Core::inst().add(Logic::inst());
	Core::inst().add(Video::inst());
	Core::inst().add(MessageSink::inst());
	Core::inst().run();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

