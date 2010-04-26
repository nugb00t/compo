#pragma once

#include "server/server_data.h"

#include "game.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LocalClientThread : public kaynine::ThreadObject {
public:
	LocalClientThread(GameFactory& game, Controls& controls)
	 : game_(game), controls_(controls) {}

	// interface: kaynine::ThreadObject
	virtual bool initialize();
	virtual bool update();
	virtual void terminate();

private:
	GameFactory& game_;
	Controls& controls_;
	
	boost::scoped_ptr<GameLocalClient> gameLocalClient_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
