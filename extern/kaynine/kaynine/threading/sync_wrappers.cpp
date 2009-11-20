#include "sync_wrappers.h"

#include <assert.h>

#include "../debug/macros.h"

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

const bool Handle::isSet() const {	
	return wait(0) == WAIT_OBJECT_0;
}

const unsigned Handle::wait(unsigned msec) const {	
	assert(handle_);
	return ::WaitForSingleObject(handle_, msec);	
}

const HANDLE Handle::handle() const {	
	assert(handle_);
	return handle_;			
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Handles::Handles(const HANDLE h0) : count_(1) {
    assert(h0);     handles_[0] = h0;   
}

Handles::Handles(const HANDLE h0, const HANDLE h1) : count_(2) {
    assert(h0);     handles_[0] = h0;
    assert(h1);     handles_[1] = h1;
}

Handles::Handles(const HANDLE h0, const HANDLE h1, const HANDLE h2) : count_(3) {
    assert(h0);     handles_[0] = h0;   
    assert(h1);     handles_[1] = h1;   
    assert(h2);     handles_[2] = h2;   
}

Handles::Handles(const HANDLE h0, const HANDLE h1, const HANDLE h2, const HANDLE h3) : count_(4) {
    assert(h0);     handles_[0] = h0;   
    assert(h1);     handles_[1] = h1;   
    assert(h2);     handles_[2] = h2;   
    assert(h3);     handles_[3] = h3;   
}

Handles::~Handles() {
    assert(0 < count_ && count_ < HANDLE_COUNT);

    for (unsigned i = 0; i < count_; ++i) {
        assert(handles_[i]);
        ::CloseHandle(handles_[i]);
    }
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

WaitableTimer::WaitableTimer(const unsigned period, const unsigned delay /*= 1*/, PTIMERAPCROUTINE func /*= NULL*/, void* arg /*= NULL*/)
: Handle(::CreateWaitableTimer(NULL, FALSE, NULL)) {
	bool ok = set(period, delay, func, arg);
	assert(ok);
}

WaitableTimer::~WaitableTimer() {
	cancel();
}

bool WaitableTimer::set(const unsigned period, const unsigned delay, PTIMERAPCROUTINE func /*= NULL*/, void* arg /*= NULL*/) {
	LARGE_INTEGER dueTime;
	dueTime.QuadPart = -(int)delay;
	return ::SetWaitableTimer(handle(), &dueTime, period, func, arg, FALSE) == TRUE;	
}

bool WaitableTimer::cancel() {	
	return ::CancelWaitableTimer(handle()) == TRUE;	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MultipleObjects::MultipleObjects(const Handle& h0) : count_(1) {
    assert(h0.handle());    handles_[0] = h0.handle();
}

MultipleObjects::MultipleObjects(const Handle& h0, const Handle& h1) : count_(2) {
    assert(h0.handle());    handles_[0] = h0.handle();
    assert(h1.handle());    handles_[1] = h1.handle();
}

MultipleObjects::MultipleObjects(const Handle& h0, const Handle& h1, const Handle& h2) : count_(3) {
    assert(h0.handle());    handles_[0] = h0.handle();
    assert(h1.handle());    handles_[1] = h1.handle();
    assert(h2.handle());    handles_[2] = h2.handle();
}

MultipleObjects::MultipleObjects(const Handle& h0, const Handle& h1, const Handle& h2, const Handle& h3) : count_(4) {
    assert(h0.handle());    handles_[0] = h0.handle();
    assert(h1.handle());    handles_[1] = h1.handle();
    assert(h2.handle());    handles_[2] = h2.handle();
    assert(h3.handle());    handles_[3] = h3.handle();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
