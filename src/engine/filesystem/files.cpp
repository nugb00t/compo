#include "stdafx.h"

#include "files.h"

#include "core/sync.h"
#include "engine.h"

using namespace engine;

File File::Null;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Files::Files() : items_(File::Null), events_(handles_, sizeof(handles_) / sizeof(HANDLE), 2) 
{
	for (uint i = 0; i < SLOT_COUNT; ++i)
		slots_[i].status = Slot::Vacant;

	handles_[0] = Sync::inst().exit.handle();
	handles_[1] = newFile_.handle();

#ifdef TRACK_DIRECTORY_CHANGES
	folder_ = ::CreateFile(_T("./"), FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL);
	assert(folder_ && folder_ != INVALID_HANDLE_VALUE);

	memset(&overlapped_, 0, sizeof(overlapped_));
	overlapped_.hEvent = handles_[SLOT_COUNT + 2];

	CHECKED_WINAPI_CALL_1_A(::ReadDirectoryChangesW(folder_, &change_, sizeof(change_), TRUE, FILE_NOTIFY_CHANGE_LAST_WRITE, NULL, &overlapped_, NULL));
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Files::~Files() {
#ifdef TRACK_DIRECTORY_CHANGES
	CHECKED_WINAPI_CALL_1_A(::CloseHandle(folder_));
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Files::update() {
	kaynine::AutoLock<> lock(guard_);

	for (unsigned check = events_.checkAny(); check != WAIT_OBJECT_0 && check != WAIT_TIMEOUT && check != WAIT_FAILED && check != WAIT_ABANDONED; check = events_.checkAny())
		if (check == WAIT_OBJECT_0 + 1) {	// new file
			schedule();
			newFile_.reset();
		}
		else if (WAIT_OBJECT_0 + 2 <= check && check < WAIT_OBJECT_0 + SLOT_COUNT + 2) {	// file read complete
			complete(check - WAIT_OBJECT_0 - 2);
			events_.reset(check, 1);
			schedule(check - WAIT_OBJECT_0 - 2);
		}
#ifdef TRACK_DIRECTORY_CHANGES
		else if (check == WAIT_OBJECT_0 + SLOT_COUNT + 2) {		// directory change notification
			events_.reset(check - WAIT_OBJECT_0, 1);
			TRACE_GOOD(_T("directory changes detected: [%d]'%s'"), change_.Action, change_.FileName);
			refresh();

			CHECKED_WINAPI_CALL_1_A(::ReadDirectoryChangesW(folder_, &change_, sizeof(change_), TRUE, FILE_NOTIFY_CHANGE_LAST_WRITE, NULL, &overlapped_, NULL));
		}
#endif

		return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const uint Files::add(const TCHAR* const path, kaynine::MemoryPool& pool) {
	assert(path);

	kaynine::AutoLock<> lock(guard_);

	// look through already added files
	Items::Range range(items_);
	for (; !range.finished(); range.next())
		if (!_tcscmp(path, range.get().path)) {
			assert(range.get().pool == &pool);

			return range.index();
		}

	const uint added = items_.add(File(path, &pool, NULL, 0, File::Pending));
	newFile_.set();

	return added;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Files::remove(const uint item) {
	kaynine::AutoLock<> lock(guard_);

	items_.remove(item);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Files::refresh() {
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Files::schedule(const unsigned first /*= 0*/) {
	assert(first < SLOT_COUNT);

	TRACE_NOTICE(_T("checking for the new files to load at the slot #%d"), first);

	Items::Range range(items_);
	for (uint slot = first; slot < SLOT_COUNT && !range.finished(); ++slot) {
		if (slots_[slot].status == Slot::Vacant) {
			while (!range.finished() && range.get().status != File::Pending)
				range.next();

			if (!range.finished()) {
				load(range.index(), slot);
				range.next();
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------

void Files::load(const uint item, const uint slot) {
	assert(item < MAX_RESOURCES && slot < SLOT_COUNT);

	TRACE_NOTICE(_T("loading '%s' in slot #%d"), items_[item].path, slot);

	// open the file
	const HANDLE handle = ::CreateFile(items_[item].path, 
									   GENERIC_READ, 
									   FILE_SHARE_READ, 
									   NULL, 
									   OPEN_EXISTING, 
									   FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FILE_FLAG_SEQUENTIAL_SCAN,
									   NULL);
	if (handle == INVALID_HANDLE_VALUE) {
		items_[item].status = File::Error;
		TRACE_WARNING(_T("couldn't open file '%s'"), items_[item].path);
		return;
	}
	
	// file size
	const DWORD size = ::GetFileSize(handle, NULL);
	if (!size) {
		CHECKED_WINAPI_CALL_1_A(::CloseHandle(handle));

		items_[item].status = File::Error;
		TRACE_WARNING(_T("couldn't load empty file '%s'"), items_[item].path);
		return;
	}

	// allocate memory for file's contents
	void* const buffer = items_[item].pool->allocate(size + sizeof(TCHAR));
	assert(buffer);
	*reinterpret_cast<TCHAR*>((unsigned)buffer + size) = _T('\0');

	// prepare asio struct
	memset(&slots_[slot].overlapped, 0, sizeof(slots_[slot].overlapped));

	assert(!events_.check(slot + 2));
	slots_[slot].overlapped.hEvent = events_.handle(slot + 2);
	
	// initiate asio read
	DWORD read = 0;
	if (!::ReadFile(handle, buffer, size, &read, &slots_[slot].overlapped) && ::GetLastError() != ERROR_IO_PENDING) {
		CHECKED_WINAPI_CALL_1_A(::CloseHandle(handle));
		TRACE_WARNING(_T("couldn't read file '%s'"), items_[item].path);

		items_[item].status = File::Error;
	} else {
		items_[item].buffer = buffer;
		items_[item].size = size;
		items_[item].status = File::Processing;
		
		slots_[slot].file = item;
		slots_[slot].handle = handle;
		slots_[slot].status = Slot::Processing;
	}
}

//---------------------------------------------------------------------------------------------------------------------

void Files::complete(const unsigned slot) {
	assert(slots_[slot].status == Slot::Processing);

	File& file = items_[slots_[slot].file];

	if (!items_.valid(slots_[slot].file)) {
		TRACE_WARNING(_T("file #%3d '%s' was discarded at the slot #%d"), slots_[slot].file, file.path, slot);
		return;
	}

	if (slots_[slot].overlapped.InternalHigh == file.size) {
		TRACE_GOOD(_T("file #%d '%s' was successfully loaded at the slot #%d"), slots_[slot].file, file.path, slot);
		file.status = File::Done;
	} else {
		TRACE_WARNING(_T("file #%d '%s' failed to load at the slot #%d"), slots_[slot].file, file.path, slot);
		file.status = File::Error;
	}

	CHECKED_WINAPI_CALL_1_A(::CloseHandle(slots_[slot].handle));

	slots_[slot].status = Slot::Vacant;
}

//---------------------------------------------------------------------------------------------------------------------
