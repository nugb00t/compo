/*******************************************************//**
    @file

    @brief	Shared memry area template

    @author Andrew Gresyk

    @date	18.11.2009
*//********************************************************/
#ifndef KN_THREAD_INCLUDED
#define KN_THREAD_INCLUDED

#include <windows.h>
#include <boost/scoped_ptr.hpp>

namespace kaynine {

class ThreadObject;
class PulseThreadObject;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Thread {
public:
    static DWORD WINAPI func(void* something);
	static HANDLE create(ThreadObject* object) { return ::CreateThread(NULL, 0, &func, object, 0, NULL); }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PulseThread {
public:
    static DWORD WINAPI func(void* something);
	static HANDLE create(PulseThreadObject* object) { return ::CreateThread(NULL, 0, &func, object, 0, NULL); }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif