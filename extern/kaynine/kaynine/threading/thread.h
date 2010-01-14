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
    struct ArgPack {
        typename TObject::Params& params;
        Event& quit;

        ArgPack(typename TObject::Params& params_, Event& quit_)
            : params(params_), quit(quit_) {}
    };

public:
    static DWORD WINAPI func(void* something) {
        ArgPack& argPack = *reinterpret_cast<ArgPack*>(something);

        if (argPack.quit.isSet() || !TObject::inst().initialize(&argPack.params))
            return (DWORD)-1;

        while (!argPack.quit.isSet())
            if (!TObject::inst().update())
                argPack.quit.set();

        TObject::inst().terminate();

        return 0;
    }

    static HANDLE create(typename TObject::Params params, Event& quit) {
        static ArgPack argPack(params, quit);

        return ::CreateThread(NULL, 0, &func, &argPack, 0, NULL);
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
    struct ArgPack {
        typename TObject::Params& params;
        Event& quit;
        const unsigned period;
        const unsigned delay;

        ArgPack(typename TObject::Params& params_, Event& quit_, const unsigned period_, const unsigned delay_)
            : params(params_), quit(quit_), period(period_), delay(delay_) {}
    };

public:
    static DWORD WINAPI func(void* something) {
        ArgPack& argPack = *reinterpret_cast<ArgPack*>(something);

        if (argPack.quit.isSet() || !TObject::inst().initialize(&argPack.params))
            return (DWORD)-1;

        WaitableTimer timer(argPack.period, argPack.delay);
        MultipleObjects events(argPack.quit, timer);

        const unsigned waitPeriod = 2 * argPack.period;
        unsigned wait;
        for (wait = events.waitAny(waitPeriod); wait != WAIT_OBJECT_0; wait = events.waitAny(waitPeriod))
            if (!TObject::inst().update())
                argPack.quit.set();
        assert(wait != WAIT_FAILED && wait != WAIT_ABANDONED);

        TObject::inst().terminate();

        return 0;
    }

    static HANDLE create(typename TObject::Params params, Event& quit, const unsigned period, const unsigned delay = 0) {
        static ArgPack argPack(params, quit, period, delay);

        return ::CreateThread(NULL, 0, &func, &argPack, 0, NULL);
    };
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif //_KN_FRAME_BUFFER_INCLUDED_