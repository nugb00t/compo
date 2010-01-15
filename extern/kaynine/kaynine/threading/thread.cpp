#include "thread.h"

#include "thread_base.h"
#include "sync_wrappers.h"

using namespace kaynine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD WINAPI Thread::func(void* something) {
    Pack& pack = *reinterpret_cast<Pack*>(something);

    if (pack.quit.isSet() || !pack.object->initialize())
        return (DWORD)-1;

    while (!pack.quit.isSet())
        if (!pack.object->update())
            pack.quit.set();

    pack.object->terminate();

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HANDLE Thread::create(ThreadBase* object, Event& quit) {
    Pack pack(object, quit);

    return ::CreateThread(NULL, 0, &func, &pack, 0, NULL);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD WINAPI PulseThread::func(void* something) {
    Pack& pack = *reinterpret_cast<Pack*>(something);

    if (pack.quit.isSet() || !pack.object->initialize())
        return (DWORD)-1;

    WaitableTimer timer(pack.period, pack.delay);
    MultipleObjects events(pack.quit, timer);

    const unsigned waitPeriod = 2 * pack.period;
    unsigned wait;
    for (wait = events.waitAny(waitPeriod); wait != WAIT_OBJECT_0; wait = events.waitAny(waitPeriod))
        if (!pack.object->update())
            pack.quit.set();
    assert(wait != WAIT_FAILED && wait != WAIT_ABANDONED);

    pack.object->terminate();

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HANDLE PulseThread::create(ThreadBase* object, Event& quit, const unsigned period, const unsigned delay) {
    Pack pack(object, quit, period, delay);

    return ::CreateThread(NULL, 0, &func, &pack, 0, NULL);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
