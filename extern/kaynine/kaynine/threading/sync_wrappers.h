/*******************************************************//**
	@file

	@brief	Win32 API synchronization objects' wrappers

	@author Andrew S. Gresyk

	@date	10.10.2005
*//********************************************************/
#ifndef _KN_SYNC_WRAPPERS_INCLUDED_
#define _KN_SYNC_WRAPPERS_INCLUDED_


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

	bool isSet() const;
	unsigned wait(unsigned dwMilliseconds = INFINITE);

protected:
	const HANDLE handle() const;

private:
	HANDLE handle_;
	bool ownsHandle_;

	friend class MultipleObjects;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Event : public Handle {
public:
	enum Ownership {
		DontTakeOwnership
	};

public:
	Event(const TCHAR* const name);
	Event(const TCHAR* const name, const Ownership);

	const bool set();
	const bool reset();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WaitableTimer : public Handle {
public:
	WaitableTimer();
	WaitableTimer(const long period, PTIMERAPCROUTINE func = NULL, void* arg = NULL);
	~WaitableTimer();

	bool set(const long period, PTIMERAPCROUTINE func = NULL, void* arg = NULL);
	bool cancel();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Timer {
public:
	Timer(const unsigned period, HWND wnd = NULL, TIMERPROC func = NULL, unsigned timer = 0) 
		: wnd_(wnd), timer_(::SetTimer(wnd, timer, period, func)) {
			assert(timer_);
	}

	~Timer() {
		::KillTimer(wnd_, timer_);
	}

private:
	HWND wnd_;
	unsigned timer_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MultipleObjects {
	MultipleObjects& operator=(const MultipleObjects&);

public:
	MultipleObjects(const Handle& h0) 
		: count_(1) {
			handles_[0] = h0.handle();
	}

	MultipleObjects(const Handle& h0, const Handle& h1)
		: count_(2) {
			handles_[0] = h0.handle();
			handles_[1] = h1.handle();
	}

	MultipleObjects(const Handle& h0, const Handle& h1, const Handle& h2)
		: count_(3) {
			handles_[0] = h0.handle();
			handles_[1] = h1.handle();
			handles_[2] = h2.handle();
	}

	MultipleObjects(const Handle& h0, const Handle& h1, const Handle& h2, const Handle& h3)
		: count_(3) {
			handles_[0] = h0.handle();
			handles_[1] = h1.handle();
			handles_[2] = h2.handle();
			handles_[3] = h3.handle();
	}

	unsigned waitAll(unsigned msec = INFINITE) { return ::WaitForMultipleObjects(count_, handles_, TRUE, msec); }
	unsigned waitAny(unsigned msec = INFINITE) { return ::WaitForMultipleObjects(count_, handles_, FALSE, msec); }

	unsigned areSetAll() { return waitAll(0); }
	unsigned areSetAny() { return waitAny(0); }

	HANDLE operator[] (const unsigned i) {
		assert(i < count_);
		return handles_[i];
	}

private:
	HANDLE handles_[4];
	const unsigned count_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} //namespace kaynine

#endif