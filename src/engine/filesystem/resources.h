#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Resource : kaynine::SafeBool<Resource> {
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

	Resource() : path(NULL), pool(NULL), buffer(NULL), size(0), status(Vacant) {}

	Resource(const TCHAR* const path_, kaynine::MemoryPool* pool_, void* buffer_, const uint size_, const Status status_) 
		: path(path_), pool(pool_), buffer(buffer_), size(size_), status(status_) {
			assert(path_ && pool_);
	}

	// interface: SafeBool
	inline bool boolean_test() const { return path && pool; }

	static Resource Null;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Resources : public kaynine::Singleton<Resources> {
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

	bool update();
	
	const uint add(const TCHAR* const path, kaynine::MemoryPool& pool);
	void remove(const uint resource);
	
	// TODO: add
	//void refresh();
	
	inline const Resource& get(const uint item) const { return items_[item]; }

private:
	void load(const uint item, const uint slot);
	void schedule(const unsigned first = 0);
	void complete(const unsigned slot);
	
private:
	Items items_;

	Slot slots_[SLOT_COUNT];
	HANDLE handles_[SLOT_COUNT + 2];

	kaynine::Event newResource_;
	kaynine::Events events_;

	kaynine::CriticalSection guard_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
