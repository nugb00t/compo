#include "stdafx.h"

#include "engine.h"
#include "core/core.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int __cdecl _tmain(int /*argc*/, _TCHAR* /*argv[]*/) {
	CHECKED_CALL(kaynine::setCurrentDirectory());

	Core core;
	core.run();

	DEBUG_ONLY(TRACE_GOOD(_T("any key please..")));
	DEBUG_ONLY(_getch());
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////