#pragma once

#include "thread_base.h"

#include <windows.h>
#include <boost/scoped_ptr.hpp>

namespace kaynine {

class ThreadObject;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class TSync>
class Thread {
public:
    static DWORD WINAPI func(void* something);

	static HANDLE create(ThreadObject* object) { 
		assert(object); 
		return ::CreateThread(NULL, 0, &func, object, 0, NULL);
	}
};

//---------------------------------------------------------------------------------------------------------------------

template<class TSync>
DWORD WINAPI Thread<TSync>::func(void* something) {
	assert(something);

	ThreadObject& object = *reinterpret_cast<ThreadObject*>(something);

	if (!TSync::inst().exit.check() && object.initialize())
		while (!TSync::inst().exit.check() && object.update());

	TSync::inst().exit.set();

	object.terminate();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class TSync, unsigned TPeriod, unsigned TDelay = 0>
class PulseThread {
public:
	static DWORD WINAPI func(void* something);

	static HANDLE create(ThreadObject* object) { 
		assert(object);
		return ::CreateThread(NULL, 0, &func, object, 0, NULL);
	}
};

//---------------------------------------------------------------------------------------------------------------------

// TPeriod:	*1 milliseconds
// TDelay:	*100 nanoseconds
template<class TSync, unsigned TPeriod, unsigned TDelay>
DWORD WINAPI PulseThread<TSync, TPeriod, TDelay>::func(void* something) {
	assert(something);
	
	ThreadObject& object = *reinterpret_cast<ThreadObject*>(something);
	WaitableTimer timer(TPeriod, TDelay);

	if (!TSync::inst().exit.check() && object.initialize()) {
		MultipleObjects events(TSync::inst().exit, timer);
		while (events.waitAny(2 * TPeriod) == WAIT_OBJECT_0 + 1 && object.update());
	}		
	TSync::inst().exit.set();

	object.terminate();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
