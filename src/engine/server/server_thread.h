#pragma once

#include "server_data.h"
#include "logic/logic.h"

#include "game_arbiter.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ServerThread : public kaynine::ThreadObject {
	static const uint HISTORY_DEPTH = 4;
	static const uint POOL_SIZE = 4;

	typedef kaynine::CyclicBuffer<ServerState, HISTORY_DEPTH> States;
	typedef kaynine::StaticArray<unsigned, ServerState::MAX_ENTITIES> Entities;

public:
	ServerThread(GameArbiter& gameArbiter, LogicFactory& logicFactory)
		: gameArbiter_(gameArbiter), logic_(logicFactory) {}

	// interface: kaynine::ThreadObject
	virtual bool initialize();
	virtual bool update();

private:
	void updateResources();

private:
	States states_;
	Entities entities_;

	Logic logic_;

	GameArbiter& gameArbiter_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
