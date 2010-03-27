#include "stdafx.h"

#include "core/core.h"
#include "game_playground/playground_game.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int __cdecl _tmain(int /*argc*/, _TCHAR* /*argv[]*/) {
	CHECKED_CALL(kaynine::setCurrentDirectory());

	Core core;
	PlaygroundGame game;

	core.run();

	//_CrtDumpMemoryLeaks();

	DEBUG_ONLY(TRACE_GOOD(_T("any key please..")));
	DEBUG_ONLY(_getch());
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
