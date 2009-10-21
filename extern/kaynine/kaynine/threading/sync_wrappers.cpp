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

WaitableTimer::WaitableTimer() 
: Handle(::CreateWaitableTimer(NULL, FALSE, NULL)) {}

WaitableTimer::WaitableTimer(const long period, PTIMERAPCROUTINE func /*= NULL*/, void* arg /*= NULL*/)
: Handle(::CreateWaitableTimer(NULL, FALSE, NULL)) {
	bool ok = set(period, func, arg);
	assert(ok);
}

WaitableTimer::~WaitableTimer() {
	cancel();
}

bool WaitableTimer::set(const long period, PTIMERAPCROUTINE func /*= NULL*/, void* arg /*= NULL*/) {
	LARGE_INTEGER dueTime;
	dueTime.QuadPart = 0ll;
	return ::SetWaitableTimer(handle(), &dueTime, period, func, arg, FALSE) == TRUE;	
}

bool WaitableTimer::cancel() {	
	return ::CancelWaitableTimer(handle()) == TRUE;	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
