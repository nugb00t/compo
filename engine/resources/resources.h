#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Resources : public kaynine::PulseThreadObject {
	static const uint PERIOD = 100;

	static const uint MAX_RESOURCES = 64;
	static const uint MAX_LOADS = 4;
	
	struct Resource {
		TCHAR path[MAX_PATH];
		void** bufferPtr;
		bool** statusPtr;

		enum STATUS {
			VACANT,
			PENDING,
			DONE
		} status;
	};
	
	struct Load {
		OVERLAPPED overlapped;
		
		enum STATUS {
			VACANT,
			PROCESSING
		} status;
	};
	
public:
	// interface: kaynine::ThreadObject
	virtual bool initialize() { reset(); return true; }
	virtual bool update();

	virtual const uint period() const { return PERIOD; }	// *1 milliseconds
	virtual const uint delay() const { return 0; }			// *100 nanoseconds

	// interface: own
	uint add(const TCHAR* const path, void** const bufferPtr, bool** const statusPtr);
	void reset();
	
private:
	void load(const Resource& item, Load& slot);
	
private:
	Resource resources_[MAX_RESOURCES];
	uint vacantResource_;
	Load loads_[MAX_LOADS];

	kaynine::CriticalSection guard_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
