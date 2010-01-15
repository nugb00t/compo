/*******************************************************//**
    @file

    @brief	Shared memry area template

    @author Andrew S. Gresyk

    @date	18.11.2009
*//********************************************************/
#ifndef KN_THREAD_INCLUDED
#define KN_THREAD_INCLUDED

#include "windows.h"

namespace kaynine {

class Threaded;
class Event;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Thread {
    struct Pack {
		Threaded* object;
        Event* quit;

        Pack(Threaded* object_, Event* quit_)
            : object(object_), quit(quit_) {}

    private:
        Pack& operator =(const Pack&);
    };

public:
    static DWORD WINAPI func(void* something);
    static HANDLE create(Threaded* object, Event* quit);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PulseThread {
    struct Pack {
		Threaded* object;
        Event* quit;
        const unsigned period;
        const unsigned delay;

        Pack(Threaded* object_, Event* quit_, const unsigned period_, const unsigned delay_)
            : object(object_), quit(quit_), period(period_), delay(delay_) {}

    private:
        Pack& operator =(const Pack&);
    };

public:
    static DWORD WINAPI func(void* something);
    static HANDLE create(Threaded* object, Event* quit, const unsigned period, const unsigned delay = 0);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif