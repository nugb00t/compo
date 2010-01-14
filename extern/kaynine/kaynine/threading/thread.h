/*******************************************************//**
    @file

    @brief	Shared memry area template

    @author Andrew S. Gresyk

    @date	18.11.2009
*//********************************************************/
#ifndef KN_THREAD_INCLUDED
#define KN_THREAD_INCLUDED

#include "sync_wrappers.h"

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  class Threaded {
//  public:
//      struct Params {};
//  public:
//      bool initialize(TObject::Params);
//      bool update();
//      void terminate();
//  };
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TObject>
class Thread {
    struct Pack {
		TObject* object;
        typename TObject::Params& params;
        Event& quit;

        Pack(TObject* object_, typename TObject::Params& params_, Event& quit_)
            : object_(object), params(params_), quit(quit_) {}
    };

public:
    static DWORD WINAPI func(void* something) {
        Pack& pack = *reinterpret_cast<Pack*>(something);

        if (pack.quit.isSet() || !pack.object.initialize(&pack.params))
            return (DWORD)-1;

        while (!pack.quit.isSet())
            if (!pack.object.update())
                pack.quit.set();

        pack.object.terminate();

        return 0;
    }

    static HANDLE create(TObject* object, typename TObject::Params params, Event& quit) {
        static Pack pack(object, params, quit);

        return ::CreateThread(NULL, 0, &func, &pack, 0, NULL);
    };
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  class PulseThreaded {
//  public:
//      struct Params {};
//  public:
//      bool initialize(TObject::Params);
//      bool update();
//      void terminate();
//  };
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TObject>
class PulseThread {
    struct Pack {
		TObject* object;
        typename TObject::Params& params;
        Event& quit;
        const unsigned period;
        const unsigned delay;

        Pack(TObject* object_, typename TObject::Params& params_, Event& quit_, const unsigned period_, const unsigned delay_)
            : object_(object), params(params_), quit(quit_), period(period_), delay(delay_) {}
    };

public:
    static DWORD WINAPI func(void* something) {
        Pack& pack = *reinterpret_cast<Pack*>(something);

        if (pack.quit.isSet() || !pack.object.initialize(&pack.params))
            return (DWORD)-1;

        WaitableTimer timer(pack.period, pack.delay);
        MultipleObjects events(pack.quit, timer);

        const unsigned waitPeriod = 2 * pack.period;
        unsigned wait;
        for (wait = events.waitAny(waitPeriod); wait != WAIT_OBJECT_0; wait = events.waitAny(waitPeriod))
            if (!pack.object.update())
                pack.quit.set();
        assert(wait != WAIT_FAILED && wait != WAIT_ABANDONED);

        pack.object.terminate();

        return 0;
    }

    static HANDLE create(TObject* object, typename TObject::Params params, Event& quit, const unsigned period, const unsigned delay = 0) {
        static Pack pack(object, params, quit, period, delay);

        return ::CreateThread(NULL, 0, &func, &pack, 0, NULL);
    };
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif //_KN_FRAME_BUFFER_INCLUDED_