#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Resources : public kaynine::PulseThreadObject {
	static const uint PERIOD = 100;

	static const uint MAX_RESOURCES = 64;
	static const uint SLOT_COUNT = 4;
	
	struct Resource {
		TCHAR path[MAX_PATH];
		kaynine::MemoryPool* pool;
		void** bufferPtr;
		bool* statusPtr;

		enum STATUS {
			VACANT,
			PENDING,
			DONE
		} status;
	};
	
	struct Slot {
		Resource* resource;
		HANDLE file;

		OVERLAPPED overlapped;
		
		enum STATUS {
			VACANT,
			PROCESSING
		} status;
	};
	
public:
	Resources() : events_(handles_, sizeof(handles_) / sizeof(HANDLE), 2) {}

	// interface: kaynine::PulseThreadObject
	virtual bool initialize();
	virtual bool update();
	
	virtual const uint period() const { return PERIOD; }	// *1 milliseconds

	// interface: own
	void reset();
	uint add(const TCHAR* const path, kaynine::MemoryPool* pool, void** const bufferPtr, bool* const statusPtr);
	
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
