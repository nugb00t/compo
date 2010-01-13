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
//  struct Threaded {
//      struct Params {};
//      static DWORD WINAPI threadFunc(void*)
//  };
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TObject>
HANDLE thread(typename TObject::Params params_) {
    static TObject::Params params(params_);
    return ::CreateThread(NULL, 0, &TObject::threadFunc, &params, 0, NULL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  struct PulseThreaded {
//      bool initialize();
//      bool update();
//      void terminate();
//  };
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TObject>
class PulseThread {
    struct Joint {
        Event& signal;
        const unsigned period;
        const unsigned delay;

        Joint(Event& signal_, const unsigned period_, const unsigned delay_)
            : signal(signal_), period(period_), delay(delay_) {}
    };

public:
    static DWORD WINAPI func(void* something) {
        Joint* params = reinterpret_cast<Joint*>(something);

        if (params->signal.isSet())
            return (DWORD)-1;

        if (!TObject::inst().initialize())
            return (DWORD)-1;

        WaitableTimer timer(params->period, params->delay);
        MultipleObjects events(params->signal, timer);

        const unsigned waitPeriod = 2 * params->period;
        unsigned wait;
        for (wait = events.waitAny(waitPeriod); wait != WAIT_OBJECT_0; wait = events.waitAny(waitPeriod))
            if (!TObject::inst().update())
                params->signal.set();
        assert(wait != WAIT_FAILED && wait != WAIT_ABANDONED);

        TObject::inst().terminate();

        return 0;
    }

    static HANDLE create(Event& signal, const unsigned period, const unsigned delay = 0) {
        static Joint joint(signal, period, delay);

        return ::CreateThread(NULL, 0, &func, &joint, 0, NULL);
    };
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif //_KN_FRAME_BUFFER_INCLUDED_