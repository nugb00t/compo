#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Video : public kaynine::PulseThreadObject {
	static const uint PERIOD = 16;
	static const uint DELAY = 8 * 10;

public:
    // interface: kaynine::PulseThreadObject
	virtual bool initialize();
    virtual bool update();
	virtual void terminate();

	virtual const uint period() const { return PERIOD; }	// *1 milliseconds
	virtual const uint delay() const { return DELAY; }		// *100 nanoseconds

protected:
	// interface: own
	virtual void doUpdate() = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
