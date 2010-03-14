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
	enum Mode {
		LOCKED
	};

private:
	CRITICAL_SECTION cs_;

public:
	// new
	inline CriticalSection()			{ ::InitializeCriticalSection(&cs_); } 
	inline CriticalSection(const Mode)	{ ::InitializeCriticalSection(&cs_); lock(); }
	inline ~CriticalSection()			{ if (isLocked()) unlock(); ::DeleteCriticalSection(&cs_); }

	inline bool tryLock()				{ return ::TryEnterCriticalSection(&cs_) == TRUE; }
	inline void lock()					{ ::EnterCriticalSection(&cs_); }
	inline void unlock()				{ ::LeaveCriticalSection(&cs_); }

	inline bool isLocked()				{ return cs_.LockCount >= 0; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T = CriticalSection>
class AutoLock {
public:
	AutoLock(T& lockable) : lockable_(lockable) { lockable_.lock(); }
	~AutoLock() { lockable_.unlock(); }

private:
	T& lockable_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Handle {
public:
	enum Mode {
		TAKE_OWNERSHIP
	};

public:
	inline Handle(const HANDLE handle)				: handle_(handle), ownsHandle_(false)			{ assert(handle_); }
	inline Handle(const Mode, const HANDLE handle)	: handle_(handle), ownsHandle_(true)			{ assert(handle_); }
	inline Handle(const Handle& handle)				: handle_(handle.handle()), ownsHandle_(false)	{ assert(handle_); }

	inline ~Handle() {
		if (handle_ && ownsHandle_)
			::CloseHandle(handle_);
	}

	inline Handle& operator =(const HANDLE handle);

	inline const bool isSet() const {
		assert(handle_);
		return wait(0) == WAIT_OBJECT_0;
	}

	inline const unsigned wait(unsigned msec = INFINITE) const {
		assert(handle_);
		return ::WaitForSingleObject(handle_, msec);
	}

	inline const HANDLE handle() const;

private:
	HANDLE handle_;
	bool ownsHandle_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Event : public Handle {
public:
	enum Mode {
		OPEN	
	};

public:
	inline Event(const TCHAR* const name = NULL)		: Handle(Handle::TAKE_OWNERSHIP, ::CreateEvent(NULL, TRUE, FALSE, name)) {}	// manual reset + non-signaled
	inline Event(const Mode, const TCHAR* const name)	: Handle(::OpenEvent(NULL, FALSE, name)) {}

	inline const bool set()		{ assert(handle()); return ::SetEvent(handle()) == TRUE; }
	inline const bool reset()	{ assert(handle()); return ::ResetEvent(handle()) == TRUE; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Handles {
public:
	inline Handles(HANDLE* const handles, const unsigned size)						: handles_(handles), size_(size), ownsHandles_(false) { assert(handles && size); }
	inline Handles(const Handle::Mode, HANDLE* const handles, const unsigned size)	: handles_(handles), size_(size), ownsHandles_(true)  { assert(handles && size); }
	inline ~Handles() { if (ownsHandles_) for (unsigned i = 0; i < size_; ++i) if (handles_[i]) ::CloseHandle(handles_[i]); }

private:
	Handles& operator=(const Handles&);

public:
	inline const unsigned waitAll(unsigned msec = INFINITE) const{
		return ::WaitForMultipleObjects(size_, handles_, TRUE, msec);
	}
	inline const unsigned waitAny(unsigned msec = INFINITE) const{ 
		return ::WaitForMultipleObjects(size_, handles_, FALSE, msec);
	}

	inline const unsigned waitAllOf(const unsigned first, const unsigned count = 0, unsigned msec = INFINITE) const;
	inline const unsigned waitAnyOf(const unsigned first, const unsigned count = 0, unsigned msec = INFINITE) const;

	inline const bool isSet(const unsigned i) const {
		assert(handles_[i]);
		return ::WaitForSingleObject(handles_[i], 0) != 0;
	}

	inline const HANDLE handle(const unsigned i) const {
		assert(handles_[i]);
		return handles_[i];
	}

protected:
	HANDLE* const handles_;
	const unsigned size_;
	const bool ownsHandles_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Events : public Handles {
public:
	Events(HANDLE* const handles, const unsigned size, const unsigned first = 0, const unsigned count = 0);
	~Events();
	
	inline const bool set(const unsigned first = 0, const unsigned count = 0);
	inline const bool reset(const unsigned first = 0, const unsigned count = 0) {
		const unsigned end = count ? first + count : count_;

		bool ok = true;
		for (unsigned i = first; i < end; ++i)
			ok &= ::ResetEvent(handles_[i]) == TRUE;

		return ok;
	}

private:
	Events& operator =(const Events&);

private:
	const unsigned first_;
	const unsigned count_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WaitableTimer : public Handle {
public:
	WaitableTimer() : Handle(::CreateWaitableTimer(NULL, FALSE, NULL)) {}
	WaitableTimer(const unsigned period, const unsigned delay = 1, PTIMERAPCROUTINE func = NULL, void* arg = NULL);
	~WaitableTimer() { cancel(); }

	bool set(const unsigned period, const unsigned delay = 1, PTIMERAPCROUTINE func = NULL, void* arg = NULL);
	bool cancel() { return ::CancelWaitableTimer(handle()) == TRUE; }
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

class MultipleObjects {
    static const unsigned HANDLE_COUNT = 4;

public:
	MultipleObjects(const Handle& h0);
	MultipleObjects(const Handle& h0, const Handle& h1);
	MultipleObjects(const Handle& h0, const Handle& h1, const Handle& h2);
	MultipleObjects(const Handle& h0, const Handle& h1, const Handle& h2, const Handle& h3);
	~MultipleObjects();

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

#ifndef _DEBUG
#include "sync_wrappers.inl"
#endif

}
