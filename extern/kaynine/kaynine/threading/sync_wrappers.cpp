#include "sync_wrappers.h"

#include <assert.h>

using namespace kaynine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CriticalSection::CriticalSection(const LOCK_STATE state) {	
	::InitializeCriticalSection(&cs_);

	if (state == LOCKED)
		lock();
}

CriticalSection::~CriticalSection() {	
	if (isLocked())
		unlock();

	::DeleteCriticalSection(&cs_);	
}

bool CriticalSection::tryLock() {	
	return ::TryEnterCriticalSection(&cs_) == TRUE;	
}

void CriticalSection::lock() {	
	::EnterCriticalSection(&cs_);
}

void CriticalSection::unlock() {	
	::LeaveCriticalSection(&cs_);
}

bool CriticalSection::isLocked() {	
	return cs_.LockCount >= 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Handle::Handle(const HANDLE handle, const bool takeOwnership)
: handle_(handle), ownsHandle_(takeOwnership) {
	assert(handle_);
}

Handle::Handle(const Handle& handle) 
: handle_(handle.handle()), ownsHandle_(false) {
	assert(handle_);
}

Handle::~Handle() {
	assert(handle_);
	if (ownsHandle_) {
		::CloseHandle(handle_);
		handle_ = NULL;
	}
}

Handle& Handle::operator =(const HANDLE handle) {
	assert(handle_);
	if (ownsHandle_)
		::CloseHandle(handle_);

	handle_ = handle;	

	return *this;
}

bool Handle::isSet() const {	
	assert(handle_);
	return ::WaitForSingleObject(handle_, 0) == WAIT_OBJECT_0;
}

unsigned Handle::wait(unsigned msec) {	
	assert(handle_);
	return ::WaitForSingleObject(handle_, msec);	
}

const HANDLE Handle::handle() const {	
	assert(handle_);
	return handle_;			
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Event::Event(const TCHAR* const name) 
: Handle(::CreateEvent(NULL, TRUE, FALSE, name), true) {}

Event::Event(const TCHAR* const name, const Ownership) 
: Handle(::OpenEvent(NULL, FALSE, name), false) {
}

const bool Event::set() {
	assert(handle());
	return ::SetEvent(handle()) == TRUE;
}

const bool Event::reset() {
	assert(handle());
	return ::ResetEvent(handle()) == TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WaitableTimer::WaitableTimer(const unsigned dueTime)
: Handle(::CreateWaitableTimer(NULL, FALSE, NULL)) {
	set(dueTime);
}

WaitableTimer::~WaitableTimer() {
	assert(handle());
	cancel();
}

bool WaitableTimer::set(const unsigned dueTime) {
	assert(handle());
	LARGE_INTEGER period;
	period.QuadPart = dueTime;
	return ::SetWaitableTimer(handle(), &period, 0, NULL, NULL, FALSE) == TRUE;	
}

bool WaitableTimer::cancel() {	
	assert(handle());
	return ::CancelWaitableTimer(handle()) == TRUE;	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
