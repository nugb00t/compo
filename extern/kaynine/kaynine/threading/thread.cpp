#include "thread.h"
#include "thread_base.h"

using namespace kaynine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD WINAPI Thread::func(void* something) {
    ThreadObject& object = *reinterpret_cast<ThreadObject*>(something);

    if (object.quit().isSet() || !object.initialize())
        return (DWORD)-1;

    while (!object.quit().isSet())
        if (!object.update())
            object.quit().set();

    object.terminate();

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DWORD WINAPI PulseThread::func(void* something) {
	PulseThreadObject& object = *reinterpret_cast<PulseThreadObject*>(something);

    if (object.quit().isSet() || !object.initialize())
        return (DWORD)-1;

    WaitableTimer timer(object.period(), object.delay());
    MultipleObjects events(object.quit(), timer);

    const unsigned waitPeriod = 2 * object.period();
    unsigned wait;
    for (wait = events.waitAny(waitPeriod); wait != WAIT_OBJECT_0; wait = events.waitAny(waitPeriod))
        if (!object.update())
            object.quit().set();
    assert(wait != WAIT_FAILED && wait != WAIT_ABANDONED);

    object.terminate();

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
