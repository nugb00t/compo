#pragma once

// std
#include <assert.h>

// win
#ifndef _WIN32_WINNT
# define _WIN32_WINNT	0x0500
#endif

#ifndef WINVER
# define WINVER			0x0500
#endif

#include <windows.h>

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CriticalSection {
public:
	enum LOCK_STATE {
		LOCKED,
		UNLOCKED
	};

private:
	CRITICAL_SECTION cs_;


public:
	// new
	explicit CriticalSection(const LOCK_STATE state = UNLOCKED);
	~CriticalSection();

	inline bool tryLock() { return ::TryEnterCriticalSection(&cs_) == TRUE; }
	inline void lock() { ::EnterCriticalSection(&cs_); }
	inline void unlock() { ::LeaveCriticalSection(&cs_); }

	inline bool isLocked() { return cs_.LockCount >= 0; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T = CriticalSection>
class AutoLock {
public:
	AutoLock(T& lockable);
	~AutoLock();

private:
	T& lockable_;
};

template<class T>
AutoLock<T>::AutoLock(T& lockable) 
: lockable_(lockable) {
	lockable_.lock();
}

template<class T>
AutoLock<T>::~AutoLock() {
	lockable_.unlock();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Handle {
public:
	Handle(const HANDLE handle, const bool takeOwnership = false);
	Handle(const Handle& handle);
	~Handle();

	Handle& operator =(const HANDLE handle);

	const bool isSet() const;
	const unsigned wait(unsigned dwMilliseconds = INFINITE) const;

	const HANDLE handle() const;

private:
	HANDLE handle_;
	bool ownsHandle_;

	friend class MultipleObjects;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Event : public Handle {
public:
	enum Mode {
		OPEN
	};

public:
	Event(const TCHAR* const name = NULL);
	Event(const Mode, const TCHAR* const name = NULL);

	const bool set();
	const bool reset();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Events {
public:
	enum Mode {
		DONT_CREATE	
	};
	
public:
	Events(const Mode, HANDLE* const handles, const unsigned count);
	Events(HANDLE* const handles, const unsigned count);
	~Events();
	
	const bool set();
	const bool reset();
	inline const unsigned waitAll(unsigned msec = INFINITE) const { return ::WaitForMultipleObjects(count_, handles_, TRUE, msec); }
	inline const unsigned waitAny(unsigned msec = INFINITE) const { return ::WaitForMultipleObjects(count_, handles_, FALSE, msec); }

private:
	Events& operator =(const Events&);
	
private:
	HANDLE* handles_;
	const unsigned count_;
	const bool ownHandles_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WaitableTimer : public Handle {
public:
	WaitableTimer();
	WaitableTimer(const unsigned period, const unsigned delay = 1, PTIMERAPCROUTINE func = NULL, void* arg = NULL);
	~WaitableTimer();

	bool set(const unsigned period, const unsigned delay = 1, PTIMERAPCROUTINE func = NULL, void* arg = NULL);
	bool cancel();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Timer {
public:
    Timer() : wnd_(NULL), timer_(NULL) {}

    Timer(const unsigned period, HWND wnd = NULL, TIMERPROC func = NULL, unsigned existing = 0) {
        set(period, wnd, func, existing);
        assert(timer_);
	}

    bool set(const unsigned period, HWND wnd = NULL, TIMERPROC func = NULL, unsigned existing = 0)  {
        wnd_ = wnd;
        timer_ = ::SetTimer(wnd, existing, period, func);

        return timer_ != NULL;
    }

	~Timer() { ::KillTimer(wnd_, timer_); }

private:
	HWND wnd_;
	unsigned timer_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Handles {
    static const unsigned HANDLE_COUNT = 4;

public:
    Handles(const HANDLE h0);
    Handles(const HANDLE h0, const HANDLE h1);
    Handles(const HANDLE h0, const HANDLE h1, const HANDLE h2);
    Handles(const HANDLE h0, const HANDLE h1, const HANDLE h2, const HANDLE h3);

    ~Handles();

private:
    Handles& operator=(const Handles&);

public:
    inline const unsigned waitAll(unsigned msec = INFINITE) const { return ::WaitForMultipleObjects(count_, handles_, TRUE, msec); }
    inline const unsigned waitAny(unsigned msec = INFINITE) const { return ::WaitForMultipleObjects(count_, handles_, FALSE, msec); }

private:
    HANDLE handles_[HANDLE_COUNT];
    const unsigned count_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MultipleObjects {
    static const unsigned HANDLE_COUNT = 4;

public:
	MultipleObjects(const Handle& h0);
	MultipleObjects(const Handle& h0, const Handle& h1);
	MultipleObjects(const Handle& h0, const Handle& h1, const Handle& h2);
	MultipleObjects(const Handle& h0, const Handle& h1, const Handle& h2, const Handle& h3);

private:
    MultipleObjects& operator=(const MultipleObjects&);

public:
	inline const unsigned waitAll(unsigned msec = INFINITE) const { return ::WaitForMultipleObjects(count_, handles_, TRUE, msec); }
	inline const unsigned waitAny(unsigned msec = INFINITE) const { return ::WaitForMultipleObjects(count_, handles_, FALSE, msec); }

private:
	HANDLE handles_[HANDLE_COUNT];
	const unsigned count_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
