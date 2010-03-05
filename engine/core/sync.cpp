#include "stdafx.h"

#include "sync.h"

using namespace engine;

namespace {
	const TCHAR* START_SIGNAL_NAME = _T("COMPONENTS_START_SIGNAL");
	//const TCHAR* STOP_SIGNAL_NAME  = _T("COMPONENTS_STOP_SIGNAL");
	const TCHAR* EXIT_SIGNAL_NAME  = _T("COMPONENTS_EXIT_SIGNAL");
}

kaynine::Event Sync::start(START_SIGNAL_NAME);
//kaynine::Event Sync::stop(STOP_SIGNAL_NAME);
kaynine::Event Sync::exit(EXIT_SIGNAL_NAME);
