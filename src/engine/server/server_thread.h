#pragma once

#include "server_data.h"
#include "logic/logic.h"

#include "game_arbiter.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ServerThread : public kaynine::PulseThreadObject {
	static const uint PERIOD = 16;
	static const uint DELAY = 4 * 10;

	static const uint HISTORY_DEPTH = 4;
	static const uint POOL_SIZE = 4;

	typedef kaynine::CyclicBuffer<ServerState, HISTORY_DEPTH> States;
	typedef kaynine::StaticArray<unsigned, ServerState::MAX_ENTITIES> Entities;

public:
	ServerThread(GameArbiter* const gameArbiter, LogicFactory* const logicFactory)
		: gameArbiter_(gameArbiter), logic_(logicFactory) {}

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

	Logic logic_;

	const boost::scoped_ptr<GameArbiter> gameArbiter_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
