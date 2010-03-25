#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Resource {
	TCHAR path[MAX_PATH];
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

	Resource(const TCHAR* const path_ = NULL, kaynine::MemoryPool* pool_ = NULL, void* buffer_ = NULL, const uint size_ = 0, const Status status_ = Vacant) 
		: pool(pool_), buffer(buffer_), size(size_), status(status_) {
			if (path_)
				_tcsncpy(&path[0], path_, MAX_PATH);
			else
				path[0] = _T('\0');
	}

	static Resource Null;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Resources : public kaynine::ThreadObject {
	static const uint MAX_RESOURCES = 64;
	static const uint SLOT_COUNT = 4;
	
	typedef kaynine::StaticArray<Resource, MAX_RESOURCES> Items;

	struct Slot {
		uint resource;
		HANDLE file;
		OVERLAPPED overlapped;

		enum Status {
			Vacant,
			Processing
		} status;
	};
	
public:
	Resources();

	// interface: kaynine::PulseThreadObject
	virtual bool update();
	
	// interface: own
	void reset();
	const uint add(const TCHAR* const path, kaynine::MemoryPool& pool);
	void remove(const uint resource);
	
	// TODO: add
	//void refresh();
	
	inline const Resource& get(const uint item) const { assert(0 <= item && item < vacant_); return resources_[item]; }

private:
	void load(const uint item, const uint slot);
	void schedule(const unsigned first = 0);
	void complete(const unsigned slot);
	
private:
	Items resources_;
	uint vacant_;

	Slot slots_[SLOT_COUNT];
	HANDLE handles_[SLOT_COUNT + 2];

	kaynine::Event newResource_;
	kaynine::Events events_;


	kaynine::CriticalSection guard_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
