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

#include "../debug/macros.h"

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
	inline AutoLock(T& lockable) : lockable_(lockable) {
		lockable_.lock();
	}

	inline ~AutoLock() {
		lockable_.unlock();
	}

private:
	AutoLock& operator =(const AutoLock&);
	
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

private:
	inline Handle& operator =(const HANDLE handle);

public:
	inline const bool isSet() const {
		assert(handle_);
		return wait(0) == WAIT_OBJECT_0;
	}

	inline const unsigned wait(unsigned msec = INFINITE) const {
		assert(handle_);
		return ::WaitForSingleObject(handle_, msec);
	}

	inline const HANDLE handle() const {
		assert(handle_);
		return handle_;
	}

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
	inline Handles(HANDLE* const handles, const unsigned size)
		: handles_(handles), size_(size), ownsHandles_(false) { assert(handles && size); }

	inline Handles(const Handle::Mode, HANDLE* const handles, const unsigned size)
		: handles_(handles), size_(size), ownsHandles_(true)  { assert(handles && size); }

	inline ~Handles() {
		if (ownsHandles_)
			for (unsigned i = 0; i < size_; ++i) {
				assert(handles_[i]);
				::CloseHandle(handles_[i]);
			}
	}

private:
	Handles& operator=(const Handles&);

public:
	inline const unsigned waitAll(unsigned msec = INFINITE) const{
		return ::WaitForMultipleObjects(size_, handles_, TRUE, msec);
	}

	inline const unsigned waitAny(unsigned msec = INFINITE) const{ 
		return ::WaitForMultipleObjects(size_, handles_, FALSE, msec);
	}

	inline const bool isSet(const unsigned i) const {
		assert(handles_[i]);
		return ::WaitForSingleObject(handles_[i], 0) == WAIT_OBJECT_0;
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
	inline Events(HANDLE* const handles, const unsigned size, const unsigned first = 0, const unsigned count = 0)
		: Handles(handles, size), first_(first), limit_(count ? first + count : size) {
			for (unsigned i = first_; i < limit_; ++i)
				handles_[i] = ::CreateEvent(NULL, TRUE, FALSE, NULL);	// manual reset + non-signaled
	}

	inline ~Events() {
		for (unsigned i = first_; i < limit_; ++i)
			::CloseHandle(handles_[i]);
	}
	
	inline const bool set(const unsigned first = 0, const unsigned count = 0) {
		const unsigned end = count ? first + count : limit_;

		bool ok = true;
		for (unsigned i = first; i < end; ++i)
			ok &= ::SetEvent(handles_[i]) == TRUE;

		return ok;
	}

	inline const bool reset(const unsigned first = 0, const unsigned count = 0) {
		const unsigned end = count ? first + count : limit_;

		bool ok = true;
		for (unsigned i = first; i < end; ++i)
			ok &= ::ResetEvent(handles_[i]) == TRUE;

		return ok;
	}

private:
	Events& operator =(const Events&);

private:
	const unsigned first_;
	const unsigned limit_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WaitableTimer : public Handle {
public:
	inline WaitableTimer() : Handle(::CreateWaitableTimer(NULL, FALSE, NULL)) {}

	inline WaitableTimer(const unsigned period, const unsigned delay = 1, PTIMERAPCROUTINE func = NULL, void* arg = NULL)
		: Handle(::CreateWaitableTimer(NULL, FALSE, NULL)) {
			DEBUG_ONLY(bool ok =)
				set(period, delay, func, arg);
			assert(ok);
	}

	inline ~WaitableTimer() { cancel(); }

	inline bool set(const unsigned period, const unsigned delay = 1, PTIMERAPCROUTINE func = NULL, void* arg = NULL) {
		LARGE_INTEGER dueTime;
		dueTime.QuadPart = -(int)delay;
		return ::SetWaitableTimer(handle(), &dueTime, period, func, arg, FALSE) == TRUE;	
	}

	inline bool cancel() { return ::CancelWaitableTimer(handle()) == TRUE; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Timer {
public:
    inline Timer() : wnd_(NULL), timer_(NULL) {}

    inline Timer(const unsigned period, HWND wnd = NULL, TIMERPROC func = NULL, unsigned existing = 0) {
        set(period, wnd, func, existing);
        assert(timer_);
	}

    inline bool set(const unsigned period, HWND wnd = NULL, TIMERPROC func = NULL, unsigned existing = 0)  {
        wnd_ = wnd;
        timer_ = ::SetTimer(wnd, existing, period, func);

        return timer_ != NULL;
    }

	inline ~Timer() { ::KillTimer(wnd_, timer_); }

private:
	HWND wnd_;
	unsigned timer_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MultipleObjects {
    static const unsigned HANDLE_COUNT = 4;

public:
	inline MultipleObjects::MultipleObjects(const Handle& h0) : count_(1) {
		assert(h0.handle());    handles_[0] = h0.handle();
	}

	inline MultipleObjects::MultipleObjects(const Handle& h0, const Handle& h1) : count_(2) {
		assert(h0.handle());    handles_[0] = h0.handle();
		assert(h1.handle());    handles_[1] = h1.handle();
	}

	inline MultipleObjects::MultipleObjects(const Handle& h0, const Handle& h1, const Handle& h2) : count_(3) {
		assert(h0.handle());    handles_[0] = h0.handle();
		assert(h1.handle());    handles_[1] = h1.handle();
		assert(h2.handle());    handles_[2] = h2.handle();
	}

	inline MultipleObjects::MultipleObjects(const Handle& h0, const Handle& h1, const Handle& h2, const Handle& h3) : count_(4) {
		assert(h0.handle());    handles_[0] = h0.handle();
		assert(h1.handle());    handles_[1] = h1.handle();
		assert(h2.handle());    handles_[2] = h2.handle();
		assert(h3.handle());    handles_[3] = h3.handle();
	}

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
//
//#ifndef _DEBUG
//#include "sync_wrappers.inl"
//#endif

}
