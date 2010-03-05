#pragma once

#include "thread_base.h"

#include <windows.h>
#include <boost/scoped_ptr.hpp>

namespace kaynine {

class ThreadObject;
class PulseThreadObject;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//struct Sync {
//	Event start;
//	Event stop;
//	Event exit;
//};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Sync>
class Thread {
public:
    static DWORD WINAPI func(void* something);
	static HANDLE create(ThreadObject* object) { return ::CreateThread(NULL, 0, &func, object, 0, NULL); }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Sync>
class PulseThread {
public:
    static DWORD WINAPI func(void* something);
	static HANDLE create(PulseThreadObject* object) { return ::CreateThread(NULL, 0, &func, object, 0, NULL); }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Sync>
DWORD WINAPI Thread<Sync>::func(void* something) {
	ThreadObject& object = *reinterpret_cast<ThreadObject*>(something);

	if (Sync::exit.isSet() || !object.initialize())
		return (DWORD)-1;

	// synchronize thread start
	Sync::start.wait();

	while (!Sync::exit.isSet())
		if (!object.update())
			Sync::exit.set();

	object.terminate();

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------

template<class Sync>
DWORD WINAPI PulseThread<Sync>::func(void* something) {
	PulseThreadObject& object = *reinterpret_cast<PulseThreadObject*>(something);

	if (Sync::exit.isSet() || !object.initialize())
		return (DWORD)-1;

	// synchronize thread start
	Sync::start.wait();
	
	WaitableTimer timer(object.period(), object.delay());
	MultipleObjects events(Sync::exit, timer);

	const unsigned waitPeriod = 2 * object.period();
	unsigned wait;
	for (wait = events.waitAny(waitPeriod); wait != WAIT_OBJECT_0; wait = events.waitAny(waitPeriod))
		if (!object.update())
			Sync::exit.set();
	assert(wait != WAIT_FAILED && wait != WAIT_ABANDONED);

	object.terminate();

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------

}
