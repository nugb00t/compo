#pragma once

#include "sync_wrappers.h"

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ThreadObject {
public:
	virtual bool initialize() { return true; }
	virtual bool update() { return true; }
	virtual void terminate() {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
