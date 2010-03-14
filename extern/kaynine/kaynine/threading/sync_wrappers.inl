///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Handle& Handle::operator =(const HANDLE handle) {
	assert(handle_);
	if (ownsHandle_)
		::CloseHandle(handle_);

	handle_ = handle;	

	return *this;
}

const HANDLE Handle::handle() const {
	assert(handle_);
	return handle_;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const unsigned Handles::waitAllOf(const unsigned first, const unsigned count /*= 0*/, unsigned msec /*= INFINITE*/) const { 
	return ::WaitForMultipleObjects(count, &handles_[first], TRUE, msec);
}

const unsigned Handles::waitAnyOf(const unsigned first, const unsigned count /*= 0*/, unsigned msec /*= INFINITE*/) const { 
	return ::WaitForMultipleObjects(count, &handles_[first], FALSE, msec);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Events::Events(HANDLE* const handles, const unsigned size, const unsigned first /*= 0*/, const unsigned count /*= 0*/)
: Handles(handles, size), first_(first), count_(count ? count : size - first) {
	for (unsigned i = first_; i < count_; ++i)
		handles_[i] = ::CreateEvent(NULL, TRUE, FALSE, NULL);	// manual reset + non-signaled
}

Events::~Events() {
	for (unsigned i = first_; i < count_; ++i)
		::CloseHandle(handles_[i]);
}

const bool Events::set(const unsigned first /*= 0*/, const unsigned count /*= 0*/) {
	const unsigned end = count ? first + count : count_;

	bool ok = true;
	for (unsigned i = first; i < end; ++i)
		ok &= ::SetEvent(handles_[i]) == TRUE;

	return ok;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WaitableTimer::WaitableTimer(const unsigned period, const unsigned delay /*= 1*/, PTIMERAPCROUTINE func /*= NULL*/, void* arg /*= NULL*/)
: Handle(::CreateWaitableTimer(NULL, FALSE, NULL)) {
	DEBUG_ONLY(bool ok =)
		set(period, delay, func, arg);
	assert(ok);
}

bool WaitableTimer::set(const unsigned period, const unsigned delay, PTIMERAPCROUTINE func /*= NULL*/, void* arg /*= NULL*/) {
	LARGE_INTEGER dueTime;
	dueTime.QuadPart = -(int)delay;
	return ::SetWaitableTimer(handle(), &dueTime, period, func, arg, FALSE) == TRUE;	
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

MultipleObjects::~MultipleObjects() {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
