/*******************************************************//**
	@file

	@brief	Win32 API synchronization objects' wrappers

	@author Andrew S. Gresyk

	@date	10.10.2005
*//********************************************************/
#ifndef _KN_SYNC_WRAPPERS_INCLUDED_
#define _KN_SYNC_WRAPPERS_INCLUDED_


// std
#include <vector>

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
private:
	CRITICAL_SECTION cs_;


public:
	// new
	explicit CriticalSection(bool initialLock = false);
	~CriticalSection();

	bool tryLock();
	void lock();
	void unlock();

	bool isLocked();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T = CriticalSection>
class AutoLock {
public:
	AutoLock(T* lockable);
	~AutoLock();

private:
	T* lockable_;
};

template<class T>
AutoLock<T>::AutoLock(T* lockable) 
: obj_(lockable) {
	lockable_->lock();
}

template<class T>
AutoLock<T>::~AutoLock() {
	lockable_->unlock();
	lockable_ = NULL;
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
	WaitableTimer(bool manualReset = false);
	~WaitableTimer();

	bool set(const LARGE_INTEGER dueTime, const bool resume = false);
	bool cancel();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MultipleObjects {
private:
	std::vector<HANDLE>		handles_;


public:
	MultipleObjects(HANDLE h0) {
		handles_.push_back(h0);
	}

	MultipleObjects(HANDLE h0, HANDLE h1) {
		handles_.reserve(2);
		handles_.push_back(h0);
		handles_.push_back(h1);
	}

	MultipleObjects(HANDLE h0, HANDLE h1, HANDLE h2) {
		handles_.reserve(3);
		handles_.push_back(h0);
		handles_.push_back(h1);
		handles_.push_back(h2);
	}

	MultipleObjects(HANDLE h0, HANDLE h1, HANDLE h2, HANDLE h3) {
		handles_.reserve(4);
		handles_.push_back(h0);
		handles_.push_back(h1);
		handles_.push_back(h2);
		handles_.push_back(h3);
	}

	DWORD areSetAll() {
		return WaitForMultipleObjects((DWORD)handles_.size(), &*handles_.begin(), TRUE, 0);
	}

	DWORD areSetAny() {
		return WaitForMultipleObjects((DWORD)handles_.size(), &*handles_.begin(), FALSE, 0);
	}

	DWORD waitAll(DWORD dwMilliseconds = INFINITE) {
		return WaitForMultipleObjects((DWORD)handles_.size(), &*handles_.begin(), TRUE, dwMilliseconds);
	}

	DWORD waitAny(DWORD dwMilliseconds = INFINITE) {
		return WaitForMultipleObjects((DWORD)handles_.size(), &*handles_.begin(), FALSE, dwMilliseconds);
	}

	HANDLE operator[] (size_t i) {
		return handles_[i];
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} //namespace kaynine

#endif