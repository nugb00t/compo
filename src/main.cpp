#include "stdafx.h"

#include "engine.h"
#include "game_playground/playground_game.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int _tmain(int /*argc*/, _TCHAR* /*argv[]*/) {
	CHECKED_CALL(kaynine::setCurrentDirectory());

	{
		engine::Engine engine(new game_playground::PlaygroundGame);
		engine.run();
	}

	_CrtDumpMemoryLeaks();

	DEBUG_ONLY(TRACE_GOOD(_T("any key please..")));
	DEBUG_ONLY(_getch());
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
