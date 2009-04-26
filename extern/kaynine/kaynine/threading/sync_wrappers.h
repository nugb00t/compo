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


class CriticalSection {
private:
	CRITICAL_SECTION	cs_;


public:
	// new
	explicit CriticalSection(bool bLock = false) {	
		InitializeCriticalSection(&cs_);

		if (bLock)
			EnterCriticalSection(&cs_);
	}

	~CriticalSection() {	
		if (isLocked())
			unlock();

		DeleteCriticalSection(&cs_);	
	}

	// by pointer
	explicit CriticalSection(CRITICAL_SECTION* pcs)
		: cs_(*pcs) {}

	inline CriticalSection& operator =(CRITICAL_SECTION* pcs) {
		cs_ = *pcs;
		return *this;
	}

	// cast
	inline operator CRITICAL_SECTION*() {	
		return &cs_;					
	}

	// tools
	inline void lock() {	
		EnterCriticalSection(&cs_);
	}

	inline bool tryLock() {	
		return TryEnterCriticalSection(&cs_) == TRUE;	
	}

	inline void unlock() {	
		LeaveCriticalSection(&cs_);
	}

	inline bool isLocked() {	
		return cs_.LockCount >= 0;
	}
};


/**
	@brief		lock
*/
template<class T = CriticalSection>
class AutoLock {
public:
	typedef T	LOCKOBJECT_TYPE;


private:
	T*			pObj_;


public:
	explicit AutoLock(T* pObj)
		: pObj_(pObj) {
		pObj_->lock();
	}

	~AutoLock() {
		pObj_->unlock();
		pObj_ = NULL;
	}
};

// CRITICAL_SECTION
template<> AutoLock<CriticalSection>::AutoLock(CriticalSection* pObj)
	: pObj_(pObj) {
		EnterCriticalSection(pObj_->operator CRITICAL_SECTION*());
}

template<> AutoLock<CriticalSection>::~AutoLock() {
	LeaveCriticalSection(pObj_->operator CRITICAL_SECTION*());
	pObj_ = NULL;
}


/**
	@brief		Handle wrapper
	
	@remarks	Main purpose is to manage handle destruction

				Does not provide duplicate facility by default for copying and assignment.
				Children have to take care of it themselves.
*/
class Handle {
protected:
	HANDLE		handle_;


public:
	Handle(HANDLE handle){
		DuplicateHandle(GetCurrentProcess(), handle, GetCurrentProcess(), &handle_ , 0, FALSE, DUPLICATE_SAME_ACCESS);	
	}

	Handle(const Handle& handle) {
		DuplicateHandle(GetCurrentProcess(), handle, GetCurrentProcess(), &handle_ , 0, FALSE, DUPLICATE_SAME_ACCESS);	
	}

	~Handle() {	
		CloseHandle(handle_);
	}

	inline Handle& operator =(HANDLE handle) {
		// close existing
		if (handle_)
			CloseHandle(handle_);

		DuplicateHandle(GetCurrentProcess(), handle, GetCurrentProcess(), &handle_ , 0, FALSE, DUPLICATE_SAME_ACCESS);	

		return *this;
	}

	inline operator HANDLE() const {	
		return handle_;			
	}

	inline HANDLE duplicate(HANDLE hSourceProcessHandle = GetCurrentProcess(), 
							HANDLE hTargetProcessHandle = GetCurrentProcess(),
							DWORD dwDesiredAccess = 0, 
							BOOL bInheritHandle = FALSE, 
							DWORD dwOptions = DUPLICATE_SAME_ACCESS) const {
		HANDLE hNew = NULL;
		DuplicateHandle(hSourceProcessHandle, handle_, hTargetProcessHandle, &hNew , dwDesiredAccess, bInheritHandle, dwOptions);	

		return hNew;
	}

	inline bool isSet() {	
		return WaitForSingleObject(handle_, 0) == WAIT_OBJECT_0;
	}

	inline DWORD wait(DWORD dwMilliseconds = INFINITE) {	
		return WaitForSingleObject(handle_, dwMilliseconds);	
	}
};


/**
	@brief	Event wrapper
*/
class Event : public Handle {
public:
	Event(bool bInitialState = false, 
				 bool bManualReset = true, 
				 LPSECURITY_ATTRIBUTES lpsaAttribute = NULL)
	: Handle(CreateEvent(lpsaAttribute, bManualReset, bInitialState, NULL)) {}

	Event(HANDLE handle)
	: Handle(handle) {}

	Event(const Event& event)
	: Handle(event) {}


	// tools
	inline bool set() {	
		return SetEvent(handle_) == TRUE;	
	}

	inline bool reset() {
		return ResetEvent(handle_) == TRUE;
	}
};


class WaitableTimer : public Handle {
public:
	// creation
	WaitableTimer(bool bManualReset = false, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL)
	: Handle(CreateWaitableTimer(lpsaAttribute, bManualReset, NULL)) {}

	// seizing
	WaitableTimer(HANDLE handle)
	: Handle(handle) {}

	~WaitableTimer() {
		CancelWaitableTimer(handle_);
	}

	// tools
	inline bool set(const LARGE_INTEGER* pDueTime, 
					LONG lMilliseconds = 0, 
					PTIMERAPCROUTINE pfnCompletionRoutine = NULL, 
					LPVOID lpArgToCompletionRoutine = NULL, 
					BOOL bResume = FALSE) {
		LARGE_INTEGER liDueTime;
		liDueTime.QuadPart = pDueTime ? pDueTime->QuadPart : -1;
		return SetWaitableTimer(handle_, &liDueTime, lMilliseconds, pfnCompletionRoutine, lpArgToCompletionRoutine, bResume) == TRUE;	
	}

	inline bool cancel() {	
		return CancelWaitableTimer(handle_) == TRUE;	
	}
};


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

	inline DWORD areSetAll() {
		return WaitForMultipleObjects((DWORD)handles_.size(), &*handles_.begin(), TRUE, 0);
	}

	inline DWORD areSetAny() {
		return WaitForMultipleObjects((DWORD)handles_.size(), &*handles_.begin(), FALSE, 0);
	}

	inline DWORD waitAll(DWORD dwMilliseconds = INFINITE) {
		return WaitForMultipleObjects((DWORD)handles_.size(), &*handles_.begin(), TRUE, dwMilliseconds);
	}

	inline DWORD waitAny(DWORD dwMilliseconds = INFINITE) {
		return WaitForMultipleObjects((DWORD)handles_.size(), &*handles_.begin(), FALSE, dwMilliseconds);
	}

	inline HANDLE operator[] (size_t i) {
		return handles_[i];
	}
};


} //namespace kaynine


#endif //_KN_SYNC_WRAPPERS_INCLUDED_