#pragma once

#define TRACK_DIRECTORY_CHANGES

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
		Processing,
		Done,
		Error,
	} status;

	File() : path(NULL), pool(NULL), buffer(NULL), size(0), status(Vacant) {}

	File(const TCHAR* const path_, kaynine::MemoryPool* pool_, void* buffer_, const uint size_, const Status status_) 
		: path(path_), pool(pool_), buffer(buffer_), size(size_), status(status_) {
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
	static const uint CHANGE_TRACK_THRESHOLD = 1000; // msec
#endif

	typedef kaynine::StaticArray<File, MAX_RESOURCES> Items;

	struct Slot {
		uint file;
		HANDLE handle;
		OVERLAPPED overlapped;

		enum Status {
			Vacant,
			Processing
		} status;
	};

#ifdef TRACK_DIRECTORY_CHANGES
	struct NotifyInfo {
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
	
	const uint add(const TCHAR* const path, kaynine::MemoryPool& pool);
	void remove(const uint item);
	
	void refresh();
	
	inline const File& get(const uint item) const { return items_[item]; }

private:
	void load(const uint item, const uint slot);
	void schedule(const unsigned first = 0);
	void complete(const unsigned slot);
	
private:
	Items items_;

	Slot slots_[SLOT_COUNT];
	
#ifdef TRACK_DIRECTORY_CHANGES
	HANDLE handles_[SLOT_COUNT + 3];	// [0: exit][1: new][2: asio*slot_count][slot_count+2: dir_watch]
	HANDLE folder_;
	OVERLAPPED overlapped_;
	NotifyInfo changes_[2];
	uint current_;
	uint lastUpdate_;
#else
	HANDLE handles_[SLOT_COUNT + 2];	// [0: exit][1: new][2: asio*slot_count]
#endif

	kaynine::Event newFile_;
	kaynine::Events events_;

	kaynine::CriticalSection guard_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
