#pragma once

#include "server_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Server : public kaynine::PulseThreadObject {
	static const uint PERIOD = 16;
	static const uint DELAY = 4 * 10;

	static const uint HISTORY_DEPTH = 4;
	static const uint POOL_SIZE = 4;

	typedef kaynine::CyclicBuffer<ServerState, HISTORY_DEPTH> States;
	typedef kaynine::StaticArray<unsigned, ServerState::MAX_ENTITIES> Entities;

public:
	// interface: kaynine::PulseThreadObject
	virtual bool initialize();
	virtual bool update();

	virtual const uint period() const { return PERIOD; }	// *1 milliseconds
	virtual const uint delay() const  { return DELAY;  }	// *100 nanoseconds

private:
	void updateResources();

private:
	States states_;
	Entities entities_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
