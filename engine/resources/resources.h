#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Resources : public kaynine::PulseThreadObject {
	static const uint PERIOD = 100;

	static const uint MAX_RESOURCES = 64;
	static const uint SLOT_COUNT = 4;
	
	struct Resource {
		TCHAR path[MAX_PATH];
		void* bufferPtr;
		bool* statusPtr;

		enum STATUS {
			VACANT,
			PENDING,
			DONE
		} status;
	};
	
	struct Slot {
		Resource* resource;
		OVERLAPPED overlapped;
		kaynine::Event event;
		
		enum STATUS {
			VACANT,
			PROCESSING
		} status;
	};
	
public:
	// interface: kaynine::PulseThreadObject
	virtual bool initialize() { reset(); return true; }
	virtual bool update();
	
	virtual const uint period() const { return PERIOD; }	// *1 milliseconds

	// interface: own
	void reset();
	uint add(const TCHAR* const path, void* const bufferPtr, bool* const statusPtr);
	
private:
	void load(Resource& item, Slot& slot);
	
private:
	Resource resources_[MAX_RESOURCES];
	uint vacant_;
	Slot slots_[SLOT_COUNT];

	kaynine::CriticalSection guard_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
