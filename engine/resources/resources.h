#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Resources : public kaynine::PulseThreadObject {
	static const uint PERIOD = 16;
	static const uint DELAY = 4 * 10;

public:
	// interface: kaynine::PulseThreadObject
	virtual kaynine::Event& quit();
	virtual const uint period() const { return PERIOD; }	// *1 milliseconds
	virtual const uint delay() const { return DELAY; }		// *100 nanoseconds

	//virtual bool initialize();
	virtual bool update();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
