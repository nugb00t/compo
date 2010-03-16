#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Resources : public kaynine::ThreadObject {
	static const uint MAX_RESOURCES = 64;
	static const uint SLOT_COUNT = 4;
	
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
	};
	
public:
	Resources();

	// interface: kaynine::PulseThreadObject
	virtual bool initialize();
	virtual bool update();
	
	// interface: own
	void reset();
	const uint add(const TCHAR* const path, kaynine::MemoryPool* pool);
	
	// TODO: add
	//void refresh();
	
	inline const Resource& get(const uint item) const { assert(0 <= item && item < vacant_); return resources_[item]; }

private:
	void load(const uint item, const uint slot);
	void schedule(const unsigned first = 0);
	void complete(const unsigned slot);
	
private:
	Resource resources_[MAX_RESOURCES];
	uint vacant_;

	Slot slots_[SLOT_COUNT];
	HANDLE handles_[SLOT_COUNT + 2];

	kaynine::Event newResource_;
	kaynine::Events events_;


	kaynine::CriticalSection guard_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
