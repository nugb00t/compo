#include "stdafx.h"

#include "playground_client.h"

using namespace engine;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameClient::handleControls(const InputData& controls, ServerRequests::Client& request) {
	const int x = controls.axis[InputData::MOUSE_X].events[0].value;
	const int y = controls.axis[InputData::MOUSE_Y].events[0].value;

	request.positionalVelocity = Vector3((float)x, (float)y, 0.f);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameClient::showWorld(const ServerState& fromArbiter, ServerState& toVideo) {
	memcpy(&toVideo, &fromArbiter, sizeof(toVideo));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
