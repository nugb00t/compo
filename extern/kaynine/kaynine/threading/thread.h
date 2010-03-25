#pragma once

#include "thread_base.h"

#include <windows.h>
#include <boost/scoped_ptr.hpp>

namespace kaynine {

class ThreadObject;
class PulseThreadObject;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Sync>
class Thread {
public:
    static DWORD WINAPI func(void* something);

	static HANDLE create(ThreadObject* object) { 
		assert(object); 
		return ::CreateThread(NULL, 0, &func, object, 0, NULL);
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Sync>
class PulseThread {
public:
    static DWORD WINAPI func(void* something);

	static HANDLE create(PulseThreadObject* object) { 
		assert(object);
		return ::CreateThread(NULL, 0, &func, object, 0, NULL);
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Sync>
DWORD WINAPI Thread<Sync>::func(void* something) {
	assert(something);

	ThreadObject& object = *reinterpret_cast<ThreadObject*>(something);

	if (!Sync::inst().exit.isSet() && object.initialize())
		while (!Sync::inst().exit.isSet() && object.update());

	Sync::inst().exit.set();

	object.terminate();

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------

template<class Sync>
DWORD WINAPI PulseThread<Sync>::func(void* something) {
	assert(something);
	
	PulseThreadObject& object = *reinterpret_cast<PulseThreadObject*>(something);
	WaitableTimer timer(object.period(), object.delay());

	if (!Sync::inst().exit.isSet() && object.initialize()) {
		MultipleObjects events(Sync::inst().exit, timer);
		while (events.waitAny(2 * object.period()) == WAIT_OBJECT_0 + 1 && object.update());
	}		
	Sync::inst().exit.set();

	object.terminate();

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------

}
