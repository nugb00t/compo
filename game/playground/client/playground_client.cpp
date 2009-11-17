#include "stdafx.h"

#include "playground_client.h"

using namespace engine;
using namespace game_playground;

namespace {
	const float AXIS_SCALE = 10.f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameClient::handleControls(const InputData& controls, ServerRequests::Client& request) {
	const float x = (float)controls.axis[InputData::MOUSE_X].events[0].value / AXIS_SCALE;
	const float y = (float)controls.axis[InputData::MOUSE_Y].events[0].value / AXIS_SCALE;

	request.positionalVelocity = Vector3(x, y, 0.f);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameClient::showWorld(const ServerState& fromArbiter, ServerState& toVideo) {
	memcpy(&toVideo, &fromArbiter, sizeof(toVideo));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
