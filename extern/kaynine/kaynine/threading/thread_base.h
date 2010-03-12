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

class PulseThreadObject : public ThreadObject {
public:
	virtual const unsigned period() const = 0;		// *1 milliseconds
	virtual const unsigned delay() { return 0; }	// *100 nanoseconds
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
