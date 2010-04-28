#pragma once

#include "server_data.h"
#include "logic/logic.h"

#include "game.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ServerThread : public kaynine::ThreadObject {
	static const uint HISTORY_DEPTH = 4;
	static const uint POOL_SIZE = 4;

	typedef kaynine::CyclicBuffer<ServerState, HISTORY_DEPTH> States;
	typedef kaynine::StaticArray<unsigned, ServerState::MAX_ENTITIES> Entities;

public:
	ServerThread(GameFactory& game) : game_(game) {}

	// interface: kaynine::ThreadObject
	virtual bool initialize();
	virtual bool update();
	virtual void terminate();

private:
	void updateFiles();

private:
	States states_;
	Entities entities_;
	
	GameFactory& game_;
	boost::scoped_ptr<GameArbiter> gameArbiter_;
	boost::scoped_ptr<GameFlow> gameFlow_;

	boost::scoped_ptr<Logic> logic_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
