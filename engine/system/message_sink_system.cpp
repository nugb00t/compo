#include "stdafx.h"

#include "message_sink_system.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MessageSinkSystem::MessageSinkSystem() {
	MessageSink::set(*this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

