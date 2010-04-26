#pragma once

#include "server/server_data.h"
#include "system/controls.h"
#include "video/video.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameArbiter {
public:
	virtual void marshall(const ServerState& last, const ServerRequests& requests, ServerState& next) = 0;

	virtual ~GameArbiter() {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameFlow {
public:
	virtual void initialize(ServerState& first) = 0;
	virtual void advance(const ServerState& last, ServerState& next) = 0;

	virtual ~GameFlow() {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameLocalClient {
public:
	virtual void handleControls(const Controls& controls, ServerRequests::Client& request) = 0;
	virtual void showWorld(const ServerState& fromArbiter, ServerState& toVideo) = 0;

	virtual ~GameLocalClient() {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LogicComponent {
public:
	virtual void decide(const ServerState& last, ServerRequests::Entity& request) = 0;

	virtual ~LogicComponent() {};
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameVideo {
public:
	virtual bool initialize(engine::Video& video) = 0;
	virtual bool update(engine::Video& video) = 0;
	virtual void terminate() = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameFactory {
public:
	virtual GameLocalClient* createLocalClient() = 0;
	virtual GameArbiter* createArbiter() = 0;
	virtual GameFlow* createFlow() = 0;
	virtual GameVideo* createVideo() = 0;
	virtual LogicComponent* createLogicComponent(const uint type) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
