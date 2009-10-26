#include "stdafx.h"

#include "core/core.h"

#include "playground/playground_game.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int __cdecl _tmain(int UNUSED(argc), _TCHAR* UNUSED(argv[])) {
	CHECKED_CALL(kaynine::setCurrentDirectory());

    Core::inst().create(Core::Windows51, Core::Direct3D9);
	game_playground::Game game;

	Core::inst().run();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

