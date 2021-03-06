#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct File : kaynine::SafeBool<File> {
	const TCHAR* path;
	kaynine::MemoryPool* pool;
	
	// state
	void* buffer;
	uint size;

	enum Status {
		Vacant,
		Pending,
		Queued,
		Aquired,
		Processed,
		Error,
	} status;
	uint object;		// back reference

	File() : path(NULL), pool(NULL), buffer(NULL), size(0), status(Vacant), object((uint)-1) {}

	File(const TCHAR* const path_, kaynine::MemoryPool* pool_, const Status status_) 
		: path(path_), pool(pool_), buffer(NULL), size(0), status(status_), object((uint)-1) {
			assert(path_ && pool_);
	}

	// interface: SafeBool
	inline bool boolean_test() const { return path && pool; }

	static File Null;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Files : public kaynine::Singleton<Files> {
	static const uint MAX_RESOURCES = 64;
	static const uint SLOT_COUNT = 4;
	
#ifdef TRACK_DIRECTORY_CHANGES
	static const uint CHANGE_THRESHOLD = 1000; // msec
	static const uint CHANGE_RETRY_DELAY = 100 * 1000; // microsec
#endif

	typedef kaynine::StaticArray<File, MAX_RESOURCES> Items;

	struct Slot {
		uint file;
		HANDLE handle;
		OVERLAPPED overlapped;

		enum Status {
			Vacant,
			Occupied
		} status;
	};

#ifdef TRACK_DIRECTORY_CHANGES
	struct NotifyInfo /*FILE_NOTIFY_INFORMATION*/ {
		DWORD NextEntryOffset;
		DWORD Action;
		DWORD FileNameLength;
		WCHAR FileName[MAX_PATH + 1];
	};
#endif
	
public:
	Files();
	~Files();

	bool update();
	
	const bool add(const TCHAR* const path, kaynine::MemoryPool& pool, uint& item);		// true if added, false if found
	void remove(const uint item);
	
	void refresh(const WCHAR* const path);
	
	inline		 File& get(const uint item)		  { return items_[item]; }
	inline const File& get(const uint item) const { return items_[item]; }

private:
	void load(const uint item, const uint slot);
	void schedule(const unsigned first = 0);
	void complete(const unsigned slot);
	
private:
	Items items_;

	Slot slots_[SLOT_COUNT];
	
#ifdef TRACK_DIRECTORY_CHANGES
	// [0:					exit]
	// [1:					new item]
	// [2 - slot_count+1:	asio complete]
	// [slot_count+2:		dir changed]
	// [slot_count+3:		load retry timer]
	HANDLE handles_[SLOT_COUNT + 4];
	HANDLE folder_;
	NotifyInfo changes_[2];
	uint change_;
	uint lastUpdate_;
	kaynine::WaitableTimer retryTimer_;
	uint retryItem_;
#else
	HANDLE handles_[SLOT_COUNT + 3];
#endif

	kaynine::Event newFile_;
	kaynine::Events events_;

	kaynine::CriticalSection guard_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
